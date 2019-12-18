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
struct usb_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_EXPLORE_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_mwait (int /*<<< orphan*/ ,void*,void*) ; 

void
usb_proc_explore_mwait(struct usb_device *udev, void *pm1, void *pm2)
{
	usb_proc_mwait(USB_BUS_EXPLORE_PROC(udev->bus), pm1, pm2);
}