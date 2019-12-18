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
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int bus_generic_probe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xenpv_attach(device_t dev)
{
	int error;

	/*
	 * Let our child drivers identify any child devices that they
	 * can find.  Once that is done attach any devices that we
	 * found.
	 */
	error = bus_generic_probe(dev);
	if (error)
		return (error);

	error = bus_generic_attach(dev);

	return (error);
}