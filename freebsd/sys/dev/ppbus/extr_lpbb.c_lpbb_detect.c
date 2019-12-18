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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ALIM ; 
 int I2CKEY ; 
 int /*<<< orphan*/  PPB_DONTWAIT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpbb_reset_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ppb_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpbb_detect(device_t dev)
{
	device_t ppbus = device_get_parent(dev);

	ppb_lock(ppbus);
	if (ppb_request_bus(ppbus, dev, PPB_DONTWAIT)) {
		ppb_unlock(ppbus);
		device_printf(dev, "can't allocate ppbus\n");
		return (0);
	}

	lpbb_reset_bus(dev);

	if ((ppb_rstr(ppbus) & I2CKEY) ||
		((ppb_rstr(ppbus) & ALIM) != ALIM)) {
		ppb_release_bus(ppbus, dev);
		ppb_unlock(ppbus);
		return (0);
	}

	ppb_release_bus(ppbus, dev);
	ppb_unlock(ppbus);

	return (1);
}