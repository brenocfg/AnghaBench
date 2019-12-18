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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  system_mtx; scalar_t__ system_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_trylock_flags_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  sx_try_slock_ (int /*<<< orphan*/ *,char const*,int) ; 

int
_vm_map_trylock_read(vm_map_t map, const char *file, int line)
{
	int error;

	error = map->system_map ?
	    !mtx_trylock_flags_(&map->system_mtx, 0, file, line) :
	    !sx_try_slock_(&map->lock, file, line);
	return (error == 0);
}