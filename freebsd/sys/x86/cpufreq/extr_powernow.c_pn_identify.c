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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AMDPM_FID ; 
 int AMDPM_VID ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int amd_pminfo ; 
 int cpu_id ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pn_identify(driver_t *driver, device_t parent)
{

	if ((amd_pminfo & AMDPM_FID) == 0 || (amd_pminfo & AMDPM_VID) == 0)
		return;
	switch (cpu_id & 0xf00) {
	case 0x600:
	case 0xf00:
		break;
	default:
		return;
	}
	if (device_find_child(parent, "powernow", -1) != NULL)
		return;
	if (BUS_ADD_CHILD(parent, 10, "powernow", -1) == NULL)
		device_printf(parent, "powernow: add child failed\n");
}