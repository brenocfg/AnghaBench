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
typedef  int /*<<< orphan*/ * vm_map_t ;

/* Variables and functions */
 int /*<<< orphan*/ * kernel_map ; 

bool
db_map_equal(vm_map_t map1, vm_map_t map2)
{
	return ((map1 == map2) ||
		((map1 == NULL) && (map2 == kernel_map)) ||
		((map1 == kernel_map) && (map2 == NULL)));
}