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
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int sx_xlocked (int /*<<< orphan*/ *) ; 

int
vm_map_locked(vm_map_t map)
{

	if (map->system_map)
		return (mtx_owned(&map->system_mtx));
	else
		return (sx_xlocked(&map->lock));
}