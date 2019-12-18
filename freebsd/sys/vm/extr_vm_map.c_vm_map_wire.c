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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 
 int vm_map_wire_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
vm_map_wire(vm_map_t map, vm_offset_t start, vm_offset_t end, int flags)
{
	int rv;

	vm_map_lock(map);
	rv = vm_map_wire_locked(map, start, end, flags);
	vm_map_unlock(map);
	return (rv);
}