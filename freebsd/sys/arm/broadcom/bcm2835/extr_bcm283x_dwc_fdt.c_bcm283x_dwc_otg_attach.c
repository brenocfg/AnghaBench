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
 int /*<<< orphan*/  BCM2835_MBOX_POWER_ID_USB_HCD ; 
 int /*<<< orphan*/  TRUE ; 
 int bcm2835_mbox_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int dwc_otg_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm283x_dwc_otg_attach(device_t dev)
{
	int err;

	err = bcm2835_mbox_set_power_state(BCM2835_MBOX_POWER_ID_USB_HCD, TRUE);
	if (err)
		device_printf(dev, "failed to set power state, err=%d\n", err);

	return (dwc_otg_attach(dev));
}