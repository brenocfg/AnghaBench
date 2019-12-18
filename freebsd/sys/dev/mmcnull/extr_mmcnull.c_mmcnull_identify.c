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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmcnull_identify(driver_t *driver, device_t parent)
{
	device_t child;

	if (resource_disabled("mmcnull", 0))
		return;

	if (device_get_unit(parent) != 0)
		return;

	/* Avoid duplicates. */
	if (device_find_child(parent, "mmcnull", -1))
		return;

	child = BUS_ADD_CHILD(parent, 20, "mmcnull", 0);
	if (child == NULL) {
		device_printf(parent, "add MMCNULL child failed\n");
		return;
	}
}