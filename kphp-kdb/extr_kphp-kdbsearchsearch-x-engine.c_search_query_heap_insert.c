#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct search_query_heap_en {scalar_t__ cpu_time; int /*<<< orphan*/  query; } ;

/* Variables and functions */
 int SEARCH_QUERY_HEAP_SIZE ; 
 struct search_query_heap_en* SQH ; 
 int SQH_SIZE ; 
 int /*<<< orphan*/  memcpy (struct search_query_heap_en*,struct search_query_heap_en*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zzfree (int /*<<< orphan*/ ,scalar_t__) ; 

void search_query_heap_insert (struct search_query_heap_en *E) {
  if (SQH_SIZE == SEARCH_QUERY_HEAP_SIZE) {
    zzfree (SQH[1].query, strlen(SQH[1].query)+1);
    int i = 1;
    while (1) {
      int j = i << 1;
      if (j > SQH_SIZE) { break; }
      if (j < SQH_SIZE && SQH[j].cpu_time > SQH[j+1].cpu_time) { j++; }
      if (E->cpu_time <= SQH[j].cpu_time) { break; }
      memcpy (SQH + i, SQH + j, sizeof (*E));
      i = j;
    }
    memcpy (SQH + i, E, sizeof (*E));
  } else {
    int i = ++SQH_SIZE;
    while (i > 1) {
      int j = (i >> 1);
      if (SQH[j].cpu_time <= E->cpu_time) { break; }
      memcpy (SQH + i, SQH + j, sizeof (*E));
      i = j;
    }
    memcpy (SQH + i, E, sizeof (*E));
  }
}