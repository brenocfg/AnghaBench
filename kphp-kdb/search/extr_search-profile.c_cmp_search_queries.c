#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cpu_time; } ;
typedef  TYPE_1__ search_query_heap_en_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_search_queries (const void *a, const void *b) {
  const search_query_heap_en_t *A = *((const search_query_heap_en_t **) a);
  const search_query_heap_en_t *B = *((const search_query_heap_en_t **) b);
  if (A->cpu_time < B->cpu_time) { return -1; }
  if (A->cpu_time > B->cpu_time) { return  1; }
  return 0;
}