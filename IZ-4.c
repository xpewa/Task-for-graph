/*
 * Вариант 3.Найти все вершины с четными степенями 
 * и отсортировать их по возрастанию степени вершины 
 * (сортировка вставками)
 * Использую граф заданный в виде матрицы инциденций
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct tVertex {
    int vertex;
    int degreeVertex;
} tVertex;

typedef struct tGraph {
    int count_vertex;
    int count_ribs;
    int** matrix;
} tGraph;

void insertion_sort(tVertex* a, int n) {
    for (int i = 1; i < n; ++i) {
        tVertex tmp = a[i];
        int j = i - 1;
        for (; j >= 0 && tmp.degreeVertex < a[j].degreeVertex; --j) {
            a[j + 1] = a[j];
        }
    a[j + 1] = tmp;
    }
}

tVertex* find_even_vertex(tGraph* graph) {
    tVertex* vertices = (tVertex*)malloc(graph->count_vertex*sizeof(tVertex));
    for (int i=0; i < graph->count_vertex; ++i) {
        vertices[i].vertex = i;
        vertices[i].degreeVertex = 0;
        for (int j=0; j < graph->count_ribs; ++j)
            if (graph->matrix[i][j] == 1)
                ++vertices[i].degreeVertex;
    }
    return vertices;
}

tGraph* create_Graph(int n, int m) {
    tGraph* Graph = (tGraph*)malloc(sizeof(tGraph));
    if (Graph == NULL) {
        printf("Failed to allocate memory!\n");
        return NULL;
    }

    Graph->count_vertex = n;
    Graph->count_ribs = m;
    Graph->matrix = (int**)malloc(n*sizeof(int*));
    if (Graph->matrix == NULL) {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    for (int i=0; i < n; ++i) {
        Graph->matrix[i] = (int*)malloc(m*sizeof(int));
        if (Graph->matrix[i] == NULL) {
            printf("Failed to allocate memory!\n");
            return NULL;
        }
    }
    return Graph;
}

void read_matrix(tGraph* Graph) {
    printf("\nEnter the matrix:\n");
    for (int i = 0; i < Graph->count_vertex; i++) 
        for (int j = 0; j < Graph->count_ribs; j++) 
            while (scanf("%d", &(Graph->matrix[i][j])) != 1 || (Graph->matrix[i][j] != 0 && Graph->matrix[i][j] != 1  &&  Graph->matrix[i][j] != -1))
                scanf("%*[^\n]");
}

int main()
{
    system("cls");
    system("color 70");
    system("title Graph");

    printf("Enter the size of the matrix x*u:\n");
    int count_vertex, count_ribs;
    while (scanf("%d", &count_vertex) != 1 || count_vertex < 0)
        scanf("%*[^\n]");
    while (scanf("%d", &count_ribs) != 1 || count_ribs < 0)
        scanf("%*[^\n]");
    tGraph* Graph = create_Graph(count_vertex, count_ribs); 
    if (NULL == Graph) {
        return -1;
    }
    read_matrix(Graph);

    tVertex* vertices = find_even_vertex(Graph);
    insertion_sort(vertices, Graph->count_vertex);
    printf("Sorting vertices:\n");
    for (int i=0; i < Graph->count_vertex; ++i) {
        printf("%d ", vertices[i].vertex);
    }

    free(vertices);
    for (int i = 0; i < Graph->count_vertex; i++) {
        free(Graph->matrix[i]);
    }
    free(Graph->matrix);
    free(Graph);

    return 0;
}