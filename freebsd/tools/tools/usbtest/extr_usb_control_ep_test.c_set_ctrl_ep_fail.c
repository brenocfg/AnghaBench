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
typedef  int /*<<< orphan*/  ss_fail ;
typedef  int /*<<< orphan*/  ds_fail ;
typedef  int /*<<< orphan*/  dev ;
typedef  int /*<<< orphan*/  bus ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
set_ctrl_ep_fail(int bus, int dev, int ds_fail, int ss_fail)
{
	int error;

	error = sysctlbyname("hw.usb.ctrl_bus_fail", NULL, NULL,
	    &bus, sizeof(bus));
	if (error != 0)
		goto emissing;

	error = sysctlbyname("hw.usb.ctrl_dev_fail", NULL, NULL,
	    &dev, sizeof(dev));
	if (error != 0)
		goto emissing;

	error = sysctlbyname("hw.usb.ctrl_ds_fail", NULL, NULL,
	    &ds_fail, sizeof(ds_fail));
	if (error != 0)
		goto emissing;

	error = sysctlbyname("hw.usb.ctrl_ss_fail", NULL, NULL,
	    &ss_fail, sizeof(ss_fail));
	if (error != 0)
		goto emissing;
	return;

emissing:
	printf("Cannot set USB sysctl, missing USB_REQ_DEBUG option?\n");
}