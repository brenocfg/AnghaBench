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
struct usb_interface_descriptor {int dummy; } ;
struct usb_interface {struct usb_interface_descriptor* idesc; } ;

/* Variables and functions */

struct usb_interface_descriptor *
usbd_get_interface_descriptor(struct usb_interface *iface)
{
	if (iface == NULL)
		return (NULL);		/* be NULL safe */
	return (iface->idesc);
}