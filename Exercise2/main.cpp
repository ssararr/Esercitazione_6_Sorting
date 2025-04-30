#include <cmath> // contiene floor e altre funzioni matematiche 
#include <iostream> // libreria per i flussi di input/output
#include <numeric> // contiene iota
#include <iostream>  
#include <sstream> // libreria per la conversione di stringhe
#include <chrono> // https://en.cppreference.com/w/cpp/chrono, libreria per la gestione e la misurazione del tempo 

#include "SortingAlgorithm.hpp" //includiamo il file di intestazione che contiene le implementazioni delle funzioni di ordinamento (BubbleSort e HeapSort)
using namespace std;
using namespace chrono;


template<typename T>
string ArrayToString(const vector<T>& v) //prendo come parametro un riferimento ad un vettore di elementi di tipo T e restituisco una stringa leggibile
{
    string str; // creo una stringa vuota
    ostringstream toString; // creo un oggetto ostringstream (manipolazione stringhe in output) per convertire il vettore in una stringa
    toString << "[ ";
    for (const T& e: v) //itero su ogni elemento di tipo T del vettore v 
        toString << e << " "; // aggiungo l'elemento alla stringa con uno spazio dopo
    toString << "]";

    return toString.str(); // restituisco il contenuto del flusso di ostringstream coime una stringa di tipo std::string usando il metodo str(). 
}

struct ClassObj // definisco una struttura ClassObj 
    // Questa struttura è un esempio di una classe che può essere ordinata.
    // Per poterla ordinare, è necessario implementare l'operatore "<" per confrontare due oggetti di questa classe.
    // In questo caso, l'ordinamento avviene in base al valore del membro "value".
    // Se non si implementa l'operatore "<", il compilatore non saprà come confrontare gli oggetti di questa classe.    
{
    double value;
};

inline bool operator< (const ClassObj& lhs, const ClassObj& rhs) 
    // Questa funzione definisce l'operatore di confronto "<" per la struttura ClassObj.
    // Permette di confrontare due oggetti di tipo ClassObj in base al loro membro "value".
    // Se lhs.value è minore di rhs.value, restituisce true, altrimenti false. (inline = la funzione può essere inserita direttamente nel punto in cui viene chiamata evitando di dover fare la chiamata una funzione)
{ 
    return lhs.value < rhs.value; 
}


int main(int argc, char *argv[])
// argc = numero di argomenti passati da riga di comando. Tale numero è sempre almeno 1, perché il primo argomento è sempre il nome del programma stesso.
// *argv = array di puntatori a caratteri che contiene gli argomenti passati da riga di comando. argv[0] è il nome del programma, argv[1] è il primo argomento, argv[2] è il secondo argomento e così via.
{
    //prendiamo la dimensione del vettore da riga di comando
    // se non viene passato un argomento, usiamo un valore di default = 10
    cout << "\nargc and argv[]:\n" << "argc: " << argc << "\nargv[]: " << endl;
    for(int a = 0; a < argc; a++) //itero su tutti gli argomenti passati da riga di comando
        cout << a << ") " << argv[a] << " "; // stampo gli argomenti passati da riga di comando
    cout << endl;

    size_t m = 10; // fisso il valore di default della dimensione di argc
    if(argc > 1)
    {
        istringstream convert(argv[1]); // converto l'argomento argv[1], ovvero il primo argomento passato dall'utente, dopo il nome del programma, in un oggetto di tipo istringstream
        convert >> m; // converto l'argomento (una stringa) in un intero
        cout << "For 'm' use value: "  << m << endl; //uso il valore fornito dall'utente come valore di m 
    }
    else
        cerr << "For 'm' use default value: "  << m << endl; //se non viene passato un argomento, uso il valore di default
    
     //COSTRUISCO V1
    vector<int> v1(m); //creo un vettore di interi di dimensione m
    std::iota(v1.begin(), v1.end(), -4); // l'ultimo argomento è il valore di partenza. Il vettore viene riempito con valori consecutivi a partire da -4 fino a raggiungere la dimensione m. 

    cout << "\nVectors: \nv1: " << endl;
    cout << ArrayToString(v1) << endl;

    //COSTRUISCO V2
    srand(2); // inizializzo il generatore di numeri casuali con un seme fisso (2) per ottenere sempre gli stessi numeri casuali
    vector<double> v2(m); //creo un vettore di double di dimensione m
    for(size_t i = 0; i < m; i++)
        v2[i] = rand() / ((double)RAND_MAX);  //riempio il vettore v2 con numeri casuali compresi tra 0 e 1. RAND_MAX è una costante definita nella libreria cstdlib che rappresenta il valore massimo restituito dalla funzione rand(); dunque la formula assicura che tutti i valori siano compresi tra 0 e 1. 

    cout << "v2: " << endl;
    cout << ArrayToString(v2) << endl;

    //COSTRUISCO V3
    vector<int> v3(m, 0); //creo un vettore di interi di dimensione m inizializzato a 0 in ogni elemento 
    for(size_t i = floor(m * 0.5) + 1; i < m; i++) //riempio parzialmente il vettore v3 a partire dall'elemento di indice m/2 + 1 in poi 
        v3[i] = rand() % 1000; //riempio il vettore v3 con numeri casuali compresi tra 0 e 999. Il modulo % restituisce il resto della divisione tra rand() e 1000, quindi i valori saranno compresi tra 0 e 999.

    copy(v1.begin(), v1.begin() + floor(m * 0.5) + 1, v3.begin()); //copio i primi m/2 + 1 elementi di v1 nei primi m/2 + 1 elementi di v3.

    //In questo modo ho creato un vettore v3 parzialmente ordinato, in cui i primi m/2 + 1 elementi sono ordinati e gli ultimi m/2 - 1 elementi sono casuali.

    cout << "v3: " << endl;
    cout << ArrayToString(v3) << endl;

    unsigned int num_experiment = 100; // numero di esperimenti da eseguire per calcolare il tempo medio di esecuzione degli algoritmi di ordinamento.
    cout << "\nSorting Times (microseconds): " << endl;
    // BUBBLESORT V1 
    double time_elapsed_bubble_v1 = 0.0;
    
    for(unsigned int t = 0; t < num_experiment; t++)
    {      
        vector<int> v(v1); //creo un vettore copia di v1 chiamato v, in modo tale da non modificare il vettore originale v1 durante l'ordinamento.
        steady_clock::time_point start_time = steady_clock::now();  //prendo il tempo di inizio dell'ordinamento
        SortLibrary::BubbleSort<int>(v); //chiamo la funzione di ordinamento BubbleSort per ordinare il vettore v (copia di v1)
        steady_clock::time_point end_time = steady_clock::now(); //prendo il tempo di fine dell'ordinamento
        time_elapsed_bubble_v1 += duration_cast<microseconds>(end_time - start_time).count(); //calcolo il tempo di esecuzione dell'ordinamento in microsecondi e lo sommo al tempo totale di esecuzione
    }
    
    time_elapsed_bubble_v1 /= num_experiment; //calcolo il tempo medio di esecuzione dell'ordinamento dividendo il tempo totale di esecuzione per il numero di esperimenti

    cout << "Bubble Sort - v1: " << time_elapsed_bubble_v1 << endl; //stampo il tempo medio di esecuzione dell'ordinamento in microsecondi


    // BUBBLESORT V2
    double time_elapsed_bubble_v2 = 0.0;
    
    for(unsigned int t = 0; t < num_experiment; t++)
    {  
        vector<double> v(v2); //creo un vettore copia di v2 chiamato v, in modo tale da non modificare il vettore originale v1 durante l'ordinamento.
        steady_clock::time_point start_time = steady_clock::now();  //prendo il tempo di inizio dell'ordinamento
        SortLibrary::BubbleSort<double>(v); //chiamo la funzione di ordinamento BubbleSort per ordinare il vettore v (copia di v1)
        steady_clock::time_point end_time = steady_clock::now(); //prendo il tempo di fine dell'ordinamento
        time_elapsed_bubble_v2 += duration_cast<microseconds>(end_time - start_time).count(); //calcolo il tempo di esecuzione dell'ordinamento in microsecondi e lo sommo al tempo totale di esecuzione
    }
    
    time_elapsed_bubble_v2 /= num_experiment; //calcolo il tempo medio di esecuzione dell'ordinamento dividendo il tempo totale di esecuzione per il numero di esperimenti

    cout << "Bubble Sort - v2: " << time_elapsed_bubble_v2 << endl; //stampo il tempo medio di esecuzione dell'ordinamento in microsecondi
    
    // BUBBLESORT V3
    double time_elapsed_bubble_v3 = 0.0;    
    for(unsigned int t = 0; t < num_experiment; t++)
    {      
        vector<int> v(v3); //creo un vettore copia di v3 chiamato v, in modo tale da non modificare il vettore originale v1 durante l'ordinamento.
        steady_clock::time_point start_time = steady_clock::now();  //prendo il tempo di inizio dell'ordinamento
        SortLibrary::BubbleSort<int>(v); //chiamo la funzione di ordinamento BubbleSort per ordinare il vettore v (copia di v1)
        steady_clock::time_point end_time = steady_clock::now(); //prendo il tempo di fine dell'ordinamento
        time_elapsed_bubble_v3 += duration_cast<microseconds>(end_time - start_time).count(); //calcolo il tempo di esecuzione dell'ordinamento in microsecondi e lo sommo al tempo totale di esecuzione
    }
    
    time_elapsed_bubble_v3 /= num_experiment; //calcolo il tempo medio di esecuzione dell'ordinamento dividendo il tempo totale di esecuzione per il numero di esperimenti

    cout << "Bubble Sort - v3: " << time_elapsed_bubble_v3 << endl; //stampo il tempo medio di esecuzione dell'ordinamento in microsecondi

    // HEAPSORT V1
    double time_elapsed_heap_v1 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v1);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_heap_v1 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v1 /= num_experiment;

    cout << "Heap Sort - v1: " << time_elapsed_heap_v1 << endl;

    // HEAPSORT V2
    double time_elapsed_heap_v2 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<double> v(v2);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<double>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_heap_v2 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v2 /= num_experiment;

    cout << "Heap Sort - v2: " << time_elapsed_heap_v2 << endl;

    // HEAPSORT V3
    double time_elapsed_heap_v3 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v3);

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        time_elapsed_heap_v3 += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v3 /= num_experiment;

    cout << "Heap Sort - v3: " << time_elapsed_heap_v3 << endl;

    return 0;
}