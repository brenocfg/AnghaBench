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
typedef  TYPE_1__* vm_map_t ;
struct TYPE_3__ {unsigned int timestamp; int /*<<< orphan*/  lock; int /*<<< orphan*/  system_mtx; scalar_t__ system_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  sx_sunlock_ (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sx_try_upgrade_ (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sx_xlock_ (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sx_xunlock_ (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  vm_map_process_deferred () ; 

int
_vm_map_lock_upgrade(vm_map_t map, const char *file, int line)
{
	unsigned int last_timestamp;

	if (map->system_map) {
		mtx_assert_(&map->system_mtx, MA_OWNED, file, line);
	} else {
		if (!sx_try_upgrade_(&map->lock, file, line)) {
			last_timestamp = map->timestamp;
			sx_sunlock_(&map->lock, file, line);
			vm_map_process_deferred();
			/*
			 * If the map's timestamp does not change while the
			 * map is unlocked, then the upgrade succeeds.
			 */
			sx_xlock_(&map->lock, file, line);
			if (last_timestamp != map->timestamp) {
				sx_xunlock_(&map->lock, file, line);
				return (1);
			}
		}
	}
	map->timestamp++;
	return (0);
}