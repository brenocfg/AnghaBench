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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_map_unlock_read (int /*<<< orphan*/ ) ; 

void
vm_map_lookup_done(vm_map_t map, vm_map_entry_t entry)
{
	/*
	 * Unlock the main-level map
	 */
	vm_map_unlock_read(map);
}