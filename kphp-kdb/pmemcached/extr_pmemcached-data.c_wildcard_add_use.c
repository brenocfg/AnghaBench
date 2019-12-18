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
struct wildcard_entry {struct wildcard_entry* prev_use; struct wildcard_entry* next_use; } ;

/* Variables and functions */
 struct wildcard_entry wildcard_use ; 

void wildcard_add_use (struct wildcard_entry *entry) {
  entry->prev_use = &wildcard_use;
  entry->next_use = wildcard_use.next_use;
  entry->prev_use->next_use = entry;
  entry->next_use->prev_use = entry;
}