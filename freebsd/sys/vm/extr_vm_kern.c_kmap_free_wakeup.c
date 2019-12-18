#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
struct TYPE_7__ {scalar_t__ needs_wakeup; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  round_page (scalar_t__) ; 
 int /*<<< orphan*/  trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_delete (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_wakeup (TYPE_1__*) ; 

void
kmap_free_wakeup(vm_map_t map, vm_offset_t addr, vm_size_t size)
{

	vm_map_lock(map);
	(void) vm_map_delete(map, trunc_page(addr), round_page(addr + size));
	if (map->needs_wakeup) {
		map->needs_wakeup = FALSE;
		vm_map_wakeup(map);
	}
	vm_map_unlock(map);
}