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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ control_hdr; scalar_t__ control_rem; } ;
struct usb_xfer {TYPE_1__ flags_int; int /*<<< orphan*/  frbuffers; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 

__attribute__((used)) static uint8_t
usbd_control_transfer_did_data(struct usb_xfer *xfer)
{
	struct usb_device_request req;

	/* SETUP packet is not yet sent */
	if (xfer->flags_int.control_hdr != 0)
		return (0);

	/* copy out the USB request header */
	usbd_copy_out(xfer->frbuffers, 0, &req, sizeof(req));

	/* compare remainder to the initial value */
	return (xfer->flags_int.control_rem != UGETW(req.wLength));
}