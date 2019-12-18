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
typedef  int /*<<< orphan*/  usb_dev_handle ;

/* Variables and functions */
 int usb_clear_halt (int /*<<< orphan*/ *,unsigned int) ; 

int
usb_resetep(usb_dev_handle * dev, unsigned int ep)
{
	/* emulate an endpoint reset through clear-STALL */
	return (usb_clear_halt(dev, ep));
}