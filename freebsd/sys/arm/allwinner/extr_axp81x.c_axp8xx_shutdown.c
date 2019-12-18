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
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXP_POWERBAT ; 
 int /*<<< orphan*/  AXP_POWERBAT_SHUTDOWN ; 
 int RB_POWEROFF ; 
 int /*<<< orphan*/  axp8xx_write (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 

__attribute__((used)) static void
axp8xx_shutdown(void *devp, int howto)
{
	device_t dev;

	if ((howto & RB_POWEROFF) == 0)
		return;

	dev = devp;

	if (bootverbose)
		device_printf(dev, "Shutdown Axp8xx\n");

	axp8xx_write(dev, AXP_POWERBAT, AXP_POWERBAT_SHUTDOWN);
}