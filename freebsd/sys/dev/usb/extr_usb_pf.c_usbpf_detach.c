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
struct usb_bus {int /*<<< orphan*/  parent; int /*<<< orphan*/ * ifp; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usbpf_clone_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbpf_cloner ; 

void
usbpf_detach(struct usb_bus *ubus)
{

	if (ubus->ifp != NULL)
		usbpf_clone_destroy(usbpf_cloner, ubus->ifp);
	if (bootverbose)
		device_printf(ubus->parent, "usbpf: Detached\n");
}