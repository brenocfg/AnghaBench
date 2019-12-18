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
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void cpu_device_release(struct device *dev)
{
	/*
	 * This is an empty function to prevent the driver core from spitting a
	 * warning at us.  Yes, I know this is directly opposite of what the
	 * documentation for the driver core and kobjects say, and the author
	 * of this code has already been publically ridiculed for doing
	 * something as foolish as this.  However, at this point in time, it is
	 * the only way to handle the issue of statically allocated cpu
	 * devices.  The different architectures will have their cpu device
	 * code reworked to properly handle this in the near future, so this
	 * function will then be changed to correctly free up the memory held
	 * by the cpu device.
	 *
	 * Never copy this way of doing things, or you too will be made fun of
	 * on the linux-kernel list, you have been warned.
	 */
}