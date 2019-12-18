#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct usb_interface {scalar_t__ num_altsetting; TYPE_2__* altsetting; } ;
struct usb_device {struct usb_interface* linux_iface_end; struct usb_interface* linux_iface_start; } ;
struct TYPE_3__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */

struct usb_interface *
usb_ifnum_to_if(struct usb_device *dev, uint8_t iface_no)
{
	struct usb_interface *p_ui;

	for (p_ui = dev->linux_iface_start;
	    p_ui != dev->linux_iface_end;
	    p_ui++) {
		if ((p_ui->num_altsetting > 0) &&
		    (p_ui->altsetting->desc.bInterfaceNumber == iface_no)) {
			return (p_ui);
		}
	}
	return (NULL);
}