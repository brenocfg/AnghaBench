#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* query; scalar_t__ expiration_time; int /*<<< orphan*/  res; int /*<<< orphan*/  cpu_time; } ;
typedef  TYPE_1__ search_query_heap_en_t ;
typedef  int /*<<< orphan*/  A ;

/* Variables and functions */
 scalar_t__ SEARCH_QUERY_EXPIRATION_TIME ; 
 TYPE_1__* SQH ; 
 int SQH_SIZE ; 
 TYPE_1__** alloca (int) ; 
 int /*<<< orphan*/  cmp_search_queries ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int strlen (char*) ; 

int search_query_worst (char *output, int olen) {
  int i;
  search_query_heap_en_t **A = alloca (SQH_SIZE * sizeof (A[0]));
  for (i = 0; i < SQH_SIZE; i++) {
    A[i] = SQH + i + 1;
  }
  qsort (A, SQH_SIZE, sizeof (A[0]), cmp_search_queries);
  char *p = output;
  for (i = SQH_SIZE - 1; i >= 0; i--) {
    if (strlen (A[i]->query) + 30 > olen) { break; }
    int l = sprintf (p, "%s\t%.6lf\t%d\t%d\n", A[i]->query, A[i]->cpu_time, A[i]->res, A[i]->expiration_time - SEARCH_QUERY_EXPIRATION_TIME);
    p += l;
    olen -= l;
  }
  return p - output;
}