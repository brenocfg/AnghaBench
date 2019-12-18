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
typedef  TYPE_1__* vm_map_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  system_mtx; scalar_t__ system_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  VM_MAP_UNLOCK_CONSISTENT (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_assert_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  sx_downgrade_ (int /*<<< orphan*/ *,char const*,int) ; 

void
_vm_map_lock_downgrade(vm_map_t map, const char *file, int line)
{

	if (map->system_map) {
		mtx_assert_(&map->system_mtx, MA_OWNED, file, line);
	} else {
		VM_MAP_UNLOCK_CONSISTENT(map);
		sx_downgrade_(&map->lock, file, line);
	}
}