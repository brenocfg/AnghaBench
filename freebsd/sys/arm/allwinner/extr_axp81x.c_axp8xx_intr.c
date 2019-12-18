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
typedef  int uint8_t ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXP_IRQSTAT1 ; 
 int AXP_IRQSTAT1_ACIN_HI ; 
 int AXP_IRQSTAT1_ACIN_LO ; 
 int AXP_IRQSTAT1_VBUS_HI ; 
 int AXP_IRQSTAT1_VBUS_LO ; 
 int /*<<< orphan*/  AXP_IRQSTAT2 ; 
 int AXP_IRQSTAT2_BATCHGC ; 
 int AXP_IRQSTAT2_BATCHGD ; 
 int AXP_IRQSTAT2_BAT_IN ; 
 int AXP_IRQSTAT2_BAT_NO ; 
 int /*<<< orphan*/  AXP_IRQSTAT3 ; 
 int /*<<< orphan*/  AXP_IRQSTAT4 ; 
 int AXP_IRQSTAT4_BATLVL_LO0 ; 
 int AXP_IRQSTAT4_BATLVL_LO1 ; 
 int /*<<< orphan*/  AXP_IRQSTAT5 ; 
 int AXP_IRQSTAT5_POKSIRQ ; 
 int /*<<< orphan*/  AXP_IRQSTAT6 ; 
 int /*<<< orphan*/  RB_POWEROFF ; 
 int axp8xx_read (void*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  axp8xx_write (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  devctl_notify (char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int /*<<< orphan*/  shutdown_nice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
axp8xx_intr(void *arg)
{
	device_t dev;
	uint8_t val;
	int error;

	dev = arg;

	error = axp8xx_read(dev, AXP_IRQSTAT1, &val, 1);
	if (error != 0)
		return;

	if (val) {
		if (bootverbose)
			device_printf(dev, "AXP_IRQSTAT1 val: %x\n", val);
		if (val & AXP_IRQSTAT1_ACIN_HI)
			devctl_notify("PMU", "AC", "plugged", NULL);
		if (val & AXP_IRQSTAT1_ACIN_LO)
			devctl_notify("PMU", "AC", "unplugged", NULL);
		if (val & AXP_IRQSTAT1_VBUS_HI)
			devctl_notify("PMU", "USB", "plugged", NULL);
		if (val & AXP_IRQSTAT1_VBUS_LO)
			devctl_notify("PMU", "USB", "unplugged", NULL);
		/* Acknowledge */
		axp8xx_write(dev, AXP_IRQSTAT1, val);
	}

	error = axp8xx_read(dev, AXP_IRQSTAT2, &val, 1);
	if (error != 0)
		return;

	if (val) {
		if (bootverbose)
			device_printf(dev, "AXP_IRQSTAT2 val: %x\n", val);
		if (val & AXP_IRQSTAT2_BATCHGD)
			devctl_notify("PMU", "Battery", "charged", NULL);
		if (val & AXP_IRQSTAT2_BATCHGC)
			devctl_notify("PMU", "Battery", "charging", NULL);
		if (val & AXP_IRQSTAT2_BAT_NO)
			devctl_notify("PMU", "Battery", "absent", NULL);
		if (val & AXP_IRQSTAT2_BAT_IN)
			devctl_notify("PMU", "Battery", "plugged", NULL);
		/* Acknowledge */
		axp8xx_write(dev, AXP_IRQSTAT2, val);
	}

	error = axp8xx_read(dev, AXP_IRQSTAT3, &val, 1);
	if (error != 0)
		return;

	if (val) {
		/* Acknowledge */
		axp8xx_write(dev, AXP_IRQSTAT3, val);
	}

	error = axp8xx_read(dev, AXP_IRQSTAT4, &val, 1);
	if (error != 0)
		return;

	if (val) {
		if (bootverbose)
			device_printf(dev, "AXP_IRQSTAT4 val: %x\n", val);
		if (val & AXP_IRQSTAT4_BATLVL_LO0)
			devctl_notify("PMU", "Battery", "shutdown threshold", NULL);
		if (val & AXP_IRQSTAT4_BATLVL_LO1)
			devctl_notify("PMU", "Battery", "warning threshold", NULL);
		/* Acknowledge */
		axp8xx_write(dev, AXP_IRQSTAT4, val);
	}

	error = axp8xx_read(dev, AXP_IRQSTAT5, &val, 1);
	if (error != 0)
		return;

	if (val != 0) {
		if ((val & AXP_IRQSTAT5_POKSIRQ) != 0) {
			if (bootverbose)
				device_printf(dev, "Power button pressed\n");
			shutdown_nice(RB_POWEROFF);
		}
		/* Acknowledge */
		axp8xx_write(dev, AXP_IRQSTAT5, val);
	}

	error = axp8xx_read(dev, AXP_IRQSTAT6, &val, 1);
	if (error != 0)
		return;

	if (val) {
		/* Acknowledge */
		axp8xx_write(dev, AXP_IRQSTAT6, val);
	}
}