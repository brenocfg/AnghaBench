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
struct TYPE_2__ {int /*<<< orphan*/  control_rem; } ;
struct usb_xfer {int endpointno; TYPE_1__ flags_int; int /*<<< orphan*/  frbuffers; } ;
struct usb_device_request {int bmRequestType; int /*<<< orphan*/  wLength; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int UE_DIR_IN ; 
 int UE_DIR_OUT ; 
 int /*<<< orphan*/  UGETW (int /*<<< orphan*/ ) ; 
 int UT_READ ; 
 int /*<<< orphan*/  usbd_copy_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 

__attribute__((used)) static void
usbd_control_transfer_init(struct usb_xfer *xfer)
{
	struct usb_device_request req;

	/* copy out the USB request header */

	usbd_copy_out(xfer->frbuffers, 0, &req, sizeof(req));

	/* setup remainder */

	xfer->flags_int.control_rem = UGETW(req.wLength);

	/* copy direction to endpoint variable */

	xfer->endpointno &= ~(UE_DIR_IN | UE_DIR_OUT);
	xfer->endpointno |=
	    (req.bmRequestType & UT_READ) ? UE_DIR_IN : UE_DIR_OUT;
}