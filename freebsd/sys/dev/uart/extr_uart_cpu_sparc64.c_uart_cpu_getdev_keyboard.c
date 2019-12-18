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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static phandle_t
uart_cpu_getdev_keyboard(char *dev, size_t devsz)
{
	char buf[sizeof("serial")];
	phandle_t input;

	if ((input = OF_finddevice("keyboard")) == -1)
		return (-1);
	if (OF_getprop(input, "device_type", buf, sizeof(buf)) == -1)
		return (-1);
	if (strcmp(buf, "serial") != 0)
		return (-1);
	if (OF_getprop(input, "name", dev, devsz) == -1)
		return (-1);
	/*
	 * So far this also matched PS/2 keyboard nodes so make sure it's
	 * one of the SCCs/UARTs known to be used to connect keyboards.
	 */
	if (strcmp(dev, "su") && strcmp(dev, "su_pnp") && strcmp(dev, "zs"))
		return (-1);
	return (input);
}