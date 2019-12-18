#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
struct TYPE_5__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  lock; scalar_t__ busy; int /*<<< orphan*/  system_mtx; scalar_t__ system_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_BUSY_WAKEUP ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_sleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_modflags (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
vm_map_wait_busy(vm_map_t map)
{

	VM_MAP_ASSERT_LOCKED(map);
	while (map->busy) {
		vm_map_modflags(map, MAP_BUSY_WAKEUP, 0);
		if (map->system_map)
			msleep(&map->busy, &map->system_mtx, 0, "mbusy", 0);
		else
			sx_sleep(&map->busy, &map->lock, 0, "mbusy", 0);
	}
	map->timestamp++;
}