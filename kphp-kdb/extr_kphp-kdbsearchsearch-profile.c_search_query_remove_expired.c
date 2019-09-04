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
struct TYPE_5__ {int expiration_time; scalar_t__ cpu_time; } ;
typedef  TYPE_1__ search_query_heap_en_t ;

/* Variables and functions */
 TYPE_1__* SQH ; 
 int SQH_SIZE ; 
 int now ; 
 int /*<<< orphan*/  search_query_heapify_back (TYPE_1__*,int) ; 
 int /*<<< orphan*/  search_query_heapify_front (TYPE_1__*,int) ; 

void search_query_remove_expired (void) {
  static int t = 0;
  if (now > t) {
    t = now + 60;
  } else {
    return;
  }
  int i;
  for (i = 1; i <= SQH_SIZE; ) {
    if (SQH[i].expiration_time < now) {
      SQH_SIZE--;
      search_query_heap_en_t *E = SQH + SQH_SIZE;
      if (i != SQH_SIZE) {
        if (SQH[i].cpu_time < E->cpu_time) {
          search_query_heapify_front (E, i);
        } else {
          search_query_heapify_back (E, i);
        }
      }
    } else {
      i++;
    }
  }
}