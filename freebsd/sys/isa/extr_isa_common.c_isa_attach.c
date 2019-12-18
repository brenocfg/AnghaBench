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
 int /*<<< orphan*/  isa_bus_device ; 

__attribute__((used)) static int
isa_attach(device_t dev)
{
	/*
	 * Arrange for isa_probe_children(dev) to be called later. XXX
	 */
	isa_bus_device = dev;
	return (0);
}