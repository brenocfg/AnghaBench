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
struct TYPE_3__ {size_t prev_bucket; size_t next_bucket; } ;
typedef  TYPE_1__ q_info ;

/* Variables and functions */
 TYPE_1__* q_entry ; 

void del_bucket (int v) {
  q_info *t = &q_entry[v];
  q_entry[t->prev_bucket].next_bucket = t->next_bucket;
  q_entry[t->next_bucket].prev_bucket = t->prev_bucket;
}