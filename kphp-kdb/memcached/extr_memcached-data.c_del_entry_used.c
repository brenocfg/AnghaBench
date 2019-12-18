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
struct TYPE_3__ {size_t next_used; size_t prev_used; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 TYPE_1__* entry_buffer ; 

void del_entry_used (int x) {
  hash_entry_t *entry = &entry_buffer[x];
  entry_buffer[entry->next_used].prev_used = entry->prev_used;
  entry_buffer[entry->prev_used].next_used = entry->next_used;
}