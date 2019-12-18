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
struct usb_bus {int /*<<< orphan*/ * ifp; } ;
struct if_clone {int dummy; } ;

/* Variables and functions */
 struct usb_bus* usbpf_ifname2ubus (char const*) ; 

__attribute__((used)) static int
usbpf_clone_match(struct if_clone *ifc, const char *name)
{
	struct usb_bus *ubus;

	ubus = usbpf_ifname2ubus(name);
	if (ubus == NULL)
		return (0);
	if (ubus->ifp != NULL)
		return (0);

	return (1);
}