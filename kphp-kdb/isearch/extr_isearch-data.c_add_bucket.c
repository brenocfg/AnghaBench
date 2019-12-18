#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int prev_bucket; int next_bucket; } ;
typedef  TYPE_1__ q_info ;

/* Variables and functions */
 TYPE_1__* q_entry ; 

void add_bucket (int x, int bucket)  {
  q_info *entry = &q_entry[x];
  int f = bucket,
      y = q_entry[bucket].prev_bucket;

  entry->next_bucket = f;
  q_entry[f].prev_bucket = x;

  entry->prev_bucket = y;
  q_entry[y].next_bucket = x;
}