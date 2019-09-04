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
struct TYPE_3__ {size_t next_time; size_t prev_time; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 TYPE_1__* entry_buffer ; 

void del_entry_time (int x) {
  hash_entry_t *entry = &entry_buffer[x];
  entry_buffer[entry->next_time].prev_time = entry->prev_time;
  entry_buffer[entry->prev_time].next_time = entry->next_time;
}