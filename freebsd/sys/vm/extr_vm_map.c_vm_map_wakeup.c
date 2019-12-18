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
struct TYPE_3__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_sleep_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
vm_map_wakeup(vm_map_t map)
{

	/*
	 * Acquire and release map_sleep_mtx to prevent a wakeup()
	 * from being performed (and lost) between the map unlock
	 * and the msleep() in _vm_map_unlock_and_wait().
	 */
	mtx_lock(&map_sleep_mtx);
	mtx_unlock(&map_sleep_mtx);
	wakeup(&map->root);
}