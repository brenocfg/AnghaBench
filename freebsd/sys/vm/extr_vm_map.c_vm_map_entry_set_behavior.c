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
typedef  TYPE_1__* vm_map_entry_t ;
typedef  int u_char ;
struct TYPE_3__ {int eflags; } ;

/* Variables and functions */
 int MAP_ENTRY_BEHAV_MASK ; 

__attribute__((used)) static inline void
vm_map_entry_set_behavior(vm_map_entry_t entry, u_char behavior)
{
	entry->eflags = (entry->eflags & ~MAP_ENTRY_BEHAV_MASK) |
	    (behavior & MAP_ENTRY_BEHAV_MASK);
}