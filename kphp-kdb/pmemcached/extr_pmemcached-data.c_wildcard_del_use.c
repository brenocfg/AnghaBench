#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wildcard_entry {TYPE_2__* prev_use; TYPE_1__* next_use; } ;
struct TYPE_4__ {TYPE_1__* next_use; } ;
struct TYPE_3__ {TYPE_2__* prev_use; } ;

/* Variables and functions */

void wildcard_del_use (struct wildcard_entry *entry) {
  entry->prev_use->next_use = entry->next_use;
  entry->next_use->prev_use = entry->prev_use;
}