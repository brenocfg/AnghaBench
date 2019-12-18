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
typedef  int /*<<< orphan*/  treespace_t ;
struct TYPE_2__ {int free_queue_cnt; int* free_queue; } ;

/* Variables and functions */
 TYPE_1__* TS_HEADER ; 

int get_treespace_free_detailed_stats (treespace_t TS, int *where) {
  int i, N = TS_HEADER->free_queue_cnt;
  int *from = TS_HEADER->free_queue + 1;
  for (i = 0; i < N; i++) {
    *where++ = *from++;
    ++from;
  }
  return N;
}