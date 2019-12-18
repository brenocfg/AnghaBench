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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_DPF (char*) ; 
 scalar_t__ AGP_MODE_GET_MODE_3 (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_STATUS ; 
 int ENXIO ; 
 scalar_t__ agp_find_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_find_display () ; 
 int agp_v2_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int agp_v3_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

int
agp_generic_enable(device_t dev, u_int32_t mode)
{
	device_t mdev = agp_find_display();
	u_int32_t tstatus, mstatus;

	if (!mdev) {
		AGP_DPF("can't find display\n");
		return ENXIO;
	}

	tstatus = pci_read_config(dev, agp_find_caps(dev) + AGP_STATUS, 4);
	mstatus = pci_read_config(mdev, agp_find_caps(mdev) + AGP_STATUS, 4);

	/*
	 * Check display and bridge for AGP v3 support.  AGP v3 allows
	 * more variety in topology than v2, e.g. multiple AGP devices
	 * attached to one bridge, or multiple AGP bridges in one
	 * system.  This doesn't attempt to address those situations,
	 * but should work fine for a classic single AGP slot system
	 * with AGP v3.
	 */
	if (AGP_MODE_GET_MODE_3(mode) &&
	    AGP_MODE_GET_MODE_3(tstatus) &&
	    AGP_MODE_GET_MODE_3(mstatus))
		return (agp_v3_enable(dev, mdev, mode));
	else
		return (agp_v2_enable(dev, mdev, mode));	    
}