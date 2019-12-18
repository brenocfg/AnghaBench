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
typedef  int /*<<< orphan*/  usb_frlength_t ;
typedef  size_t usb_frcount_t ;
struct TYPE_3__ {int /*<<< orphan*/  ext_buffer; } ;
struct usb_xfer {size_t max_frame_count; int /*<<< orphan*/  local_buffer; TYPE_2__* frbuffers; TYPE_1__ flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  USB_ADD_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
usbd_xfer_set_frame_offset(struct usb_xfer *xfer, usb_frlength_t offset,
    usb_frcount_t frindex)
{
	KASSERT(!xfer->flags.ext_buffer, ("Cannot offset data frame "
	    "when the USB buffer is external\n"));
	KASSERT(frindex < xfer->max_frame_count, ("frame index overflow"));

	/* set virtual address to load */
	xfer->frbuffers[frindex].buffer =
	    USB_ADD_BYTES(xfer->local_buffer, offset);
}