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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int bus_generic_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isavga_devclass ; 
 int /*<<< orphan*/  vga_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vgapm_resume(device_t dev)
{
	device_t vga_dev;

	vga_dev = devclass_get_device(isavga_devclass, 0);
	if (vga_dev != NULL)
		vga_resume(vga_dev);

	return (bus_generic_resume(dev));
}