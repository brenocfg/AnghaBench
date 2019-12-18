#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  rid; } ;
typedef  TYPE_1__ atkbdc_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int bus_get_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int) ; 

int
atkbdc_print_child(device_t bus, device_t dev)
{
	atkbdc_device_t *kbdcdev;
	rman_res_t irq;
	int flags;
	int retval = 0;

	kbdcdev = (atkbdc_device_t *)device_get_ivars(dev);

	retval += bus_print_child_header(bus, dev);
	flags = device_get_flags(dev);
	if (flags != 0)
		retval += printf(" flags 0x%x", flags);
	irq = bus_get_resource_start(dev, SYS_RES_IRQ, kbdcdev->rid);
	if (irq != 0)
		retval += printf(" irq %jd", irq);
	retval += bus_print_child_footer(bus, dev);

	return (retval);
}