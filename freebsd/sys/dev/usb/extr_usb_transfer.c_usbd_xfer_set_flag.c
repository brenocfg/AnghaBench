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
struct TYPE_2__ {int force_short_xfer; int short_xfer_ok; int short_frames_ok; int manual_status; } ;
struct usb_xfer {TYPE_1__ flags; } ;

/* Variables and functions */
#define  USB_FORCE_SHORT_XFER 131 
#define  USB_MANUAL_STATUS 130 
#define  USB_MULTI_SHORT_OK 129 
#define  USB_SHORT_XFER_OK 128 

void
usbd_xfer_set_flag(struct usb_xfer *xfer, int flag)
{
	switch (flag) {
		case USB_FORCE_SHORT_XFER:
			xfer->flags.force_short_xfer = 1;
			break;
		case USB_SHORT_XFER_OK:
			xfer->flags.short_xfer_ok = 1;
			break;
		case USB_MULTI_SHORT_OK:
			xfer->flags.short_frames_ok = 1;
			break;
		case USB_MANUAL_STATUS:
			xfer->flags.manual_status = 1;
			break;
	}
}