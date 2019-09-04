#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next_time; struct TYPE_4__* prev_time; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void del_entry_time (hash_entry_t *entry) {
  assert (entry);
  //assert (0 <= x && x < MAX_HASH_TABLE_SIZE + TIME_TABLE_SIZE + 1);

  assert (entry->prev_time);
  assert (entry->next_time);
  entry->next_time->prev_time = entry->prev_time;
  entry->prev_time->next_time = entry->next_time;
}