#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ control_xfr; scalar_t__ control_hdr; scalar_t__ usb_mode; } ;
struct usb_xfer {TYPE_1__ flags_int; } ;

/* Variables and functions */
 int USB_GET_DATA_ISREAD (struct usb_xfer*) ; 
 scalar_t__ USB_MODE_DEVICE ; 

__attribute__((used)) static int
usbpf_xfer_frame_is_read(struct usb_xfer *xfer, uint32_t frame)
{
	int isread;

	if ((frame == 0) && (xfer->flags_int.control_xfr != 0) &&
	    (xfer->flags_int.control_hdr != 0)) {
		/* special case */
		if (xfer->flags_int.usb_mode == USB_MODE_DEVICE) {
			/* The device controller writes to memory */
			isread = 1;
		} else {
			/* The host controller reads from memory */
			isread = 0;
		}
	} else {
		isread = USB_GET_DATA_ISREAD(xfer);
	}
	return (isread);
}