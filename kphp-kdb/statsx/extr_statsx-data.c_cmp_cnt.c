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
struct TYPE_2__ {scalar_t__ counter_id; scalar_t__ created_at; } ;

/* Variables and functions */
 TYPE_1__** Counters ; 

int cmp_cnt (const void *_a, const void *_b) { 
  int a = *(int *)_a;
  int b = *(int *)_b;
  if (Counters[a]->counter_id < Counters[b]->counter_id) return -1;
  if (Counters[a]->counter_id > Counters[b]->counter_id) return 1;
  if (Counters[a]->created_at < Counters[b]->created_at) return 1;
  if (Counters[a]->created_at > Counters[b]->created_at) return -1;
  return 0;
}