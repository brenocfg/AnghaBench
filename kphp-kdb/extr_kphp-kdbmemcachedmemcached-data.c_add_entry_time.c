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
struct TYPE_3__ {int prev_time; int next_time; int /*<<< orphan*/  exp_time; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 size_t GET_TIME_ID (int /*<<< orphan*/ ) ; 
 TYPE_1__* entry_buffer ; 
 int* time_st ; 

void add_entry_time (int x) {
  hash_entry_t *entry = &entry_buffer[x];

  int f = time_st[GET_TIME_ID (entry->exp_time)];
  int y = entry_buffer[f].prev_time;

  entry->next_time = f;
  entry_buffer[f].prev_time = x;

  entry->prev_time = y;
  entry_buffer[y].next_time = x;
}