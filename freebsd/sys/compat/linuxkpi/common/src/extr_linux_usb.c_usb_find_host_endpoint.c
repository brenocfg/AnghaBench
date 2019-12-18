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
typedef  int uint8_t ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {struct usb_host_endpoint* endpoint; TYPE_1__ desc; } ;
struct TYPE_4__ {int bEndpointAddress; int bmAttributes; } ;
struct usb_host_endpoint {TYPE_2__ desc; } ;
struct usb_device {struct usb_host_endpoint ep0; struct usb_interface* linux_iface_end; struct usb_interface* linux_iface_start; } ;

/* Variables and functions */
 int UE_ADDR ; 
 int UE_CONTROL ; 
 int UE_DIR_IN ; 
 int UE_DIR_OUT ; 
 int UE_XFERTYPE ; 

struct usb_host_endpoint *
usb_find_host_endpoint(struct usb_device *dev, uint8_t type, uint8_t ep)
{
	struct usb_host_endpoint *uhe;
	struct usb_host_endpoint *uhe_end;
	struct usb_host_interface *uhi;
	struct usb_interface *ui;
	uint8_t ea;
	uint8_t at;
	uint8_t mask;

	if (dev == NULL) {
		return (NULL);
	}
	if (type == UE_CONTROL) {
		mask = UE_ADDR;
	} else {
		mask = (UE_DIR_IN | UE_DIR_OUT | UE_ADDR);
	}

	ep &= mask;

	/*
	 * Iterate over all the interfaces searching the selected alternate
	 * setting only, and all belonging endpoints.
	 */
	for (ui = dev->linux_iface_start;
	    ui != dev->linux_iface_end;
	    ui++) {
		uhi = ui->cur_altsetting;
		if (uhi) {
			uhe_end = uhi->endpoint + uhi->desc.bNumEndpoints;
			for (uhe = uhi->endpoint;
			    uhe != uhe_end;
			    uhe++) {
				ea = uhe->desc.bEndpointAddress;
				at = uhe->desc.bmAttributes;

				if (((ea & mask) == ep) &&
				    ((at & UE_XFERTYPE) == type)) {
					return (uhe);
				}
			}
		}
	}

	if ((type == UE_CONTROL) && ((ep & UE_ADDR) == 0)) {
		return (&dev->ep0);
	}
	return (NULL);
}