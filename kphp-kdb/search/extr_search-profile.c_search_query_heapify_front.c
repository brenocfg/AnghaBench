#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cpu_time; } ;
typedef  TYPE_1__ search_query_heap_en_t ;

/* Variables and functions */
 TYPE_1__* SQH ; 
 int SQH_SIZE ; 
 int /*<<< orphan*/  search_query_copy (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void search_query_heapify_front (search_query_heap_en_t *E, int i) {
  while (1) {
    int j = i << 1;
    if (j > SQH_SIZE) { break; }
    if (j < SQH_SIZE && SQH[j].cpu_time > SQH[j+1].cpu_time) { j++; }
    if (E->cpu_time <= SQH[j].cpu_time) { break; }
    search_query_copy (SQH + i, SQH + j);
    i = j;
  }
  search_query_copy (SQH + i, E);
}