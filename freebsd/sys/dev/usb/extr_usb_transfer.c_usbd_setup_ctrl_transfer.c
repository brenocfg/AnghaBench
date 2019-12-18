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
typedef  int usb_frlength_t ;
struct TYPE_4__ {int control_act; int control_stall; int control_hdr; scalar_t__ usb_mode; int control_rem; int /*<<< orphan*/  control_did_data; } ;
struct TYPE_3__ {scalar_t__ manual_status; scalar_t__ force_short_xfer; scalar_t__ stall_pipe; } ;
struct usb_xfer {int nframes; int sumlen; int* frlengths; int max_data_length; TYPE_2__ flags_int; TYPE_1__ flags; } ;
struct usb_device_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  usbd_control_transfer_did_data (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_control_transfer_init (struct usb_xfer*) ; 

__attribute__((used)) static int
usbd_setup_ctrl_transfer(struct usb_xfer *xfer)
{
	usb_frlength_t len;

	/* Check for control endpoint stall */
	if (xfer->flags.stall_pipe && xfer->flags_int.control_act) {
		/* the control transfer is no longer active */
		xfer->flags_int.control_stall = 1;
		xfer->flags_int.control_act = 0;
	} else {
		/* don't stall control transfer by default */
		xfer->flags_int.control_stall = 0;
	}

	/* Check for invalid number of frames */
	if (xfer->nframes > 2) {
		/*
		 * If you need to split a control transfer, you
		 * have to do one part at a time. Only with
		 * non-control transfers you can do multiple
		 * parts a time.
		 */
		DPRINTFN(0, "Too many frames: %u\n",
		    (unsigned int)xfer->nframes);
		goto error;
	}

	/*
         * Check if there is a control
         * transfer in progress:
         */
	if (xfer->flags_int.control_act) {

		if (xfer->flags_int.control_hdr) {

			/* clear send header flag */

			xfer->flags_int.control_hdr = 0;

			/* setup control transfer */
			if (xfer->flags_int.usb_mode == USB_MODE_DEVICE) {
				usbd_control_transfer_init(xfer);
			}
		}
		/* get data length */

		len = xfer->sumlen;

	} else {

		/* the size of the SETUP structure is hardcoded ! */

		if (xfer->frlengths[0] != sizeof(struct usb_device_request)) {
			DPRINTFN(0, "Wrong framelength %u != %zu\n",
			    xfer->frlengths[0], sizeof(struct
			    usb_device_request));
			goto error;
		}
		/* check USB mode */
		if (xfer->flags_int.usb_mode == USB_MODE_DEVICE) {

			/* check number of frames */
			if (xfer->nframes != 1) {
				/*
			         * We need to receive the setup
			         * message first so that we know the
			         * data direction!
			         */
				DPRINTF("Misconfigured transfer\n");
				goto error;
			}
			/*
			 * Set a dummy "control_rem" value.  This
			 * variable will be overwritten later by a
			 * call to "usbd_control_transfer_init()" !
			 */
			xfer->flags_int.control_rem = 0xFFFF;
		} else {

			/* setup "endpoint" and "control_rem" */

			usbd_control_transfer_init(xfer);
		}

		/* set transfer-header flag */

		xfer->flags_int.control_hdr = 1;

		/* get data length */

		len = (xfer->sumlen - sizeof(struct usb_device_request));
	}

	/* update did data flag */

	xfer->flags_int.control_did_data =
	    usbd_control_transfer_did_data(xfer);

	/* check if there is a length mismatch */

	if (len > xfer->flags_int.control_rem) {
		DPRINTFN(0, "Length (%d) greater than "
		    "remaining length (%d)\n", len,
		    xfer->flags_int.control_rem);
		goto error;
	}
	/* check if we are doing a short transfer */

	if (xfer->flags.force_short_xfer) {
		xfer->flags_int.control_rem = 0;
	} else {
		if ((len != xfer->max_data_length) &&
		    (len != xfer->flags_int.control_rem) &&
		    (xfer->nframes != 1)) {
			DPRINTFN(0, "Short control transfer without "
			    "force_short_xfer set\n");
			goto error;
		}
		xfer->flags_int.control_rem -= len;
	}

	/* the status part is executed when "control_act" is 0 */

	if ((xfer->flags_int.control_rem > 0) ||
	    (xfer->flags.manual_status)) {
		/* don't execute the STATUS stage yet */
		xfer->flags_int.control_act = 1;

		/* sanity check */
		if ((!xfer->flags_int.control_hdr) &&
		    (xfer->nframes == 1)) {
			/*
		         * This is not a valid operation!
		         */
			DPRINTFN(0, "Invalid parameter "
			    "combination\n");
			goto error;
		}
	} else {
		/* time to execute the STATUS stage */
		xfer->flags_int.control_act = 0;
	}
	return (0);			/* success */

error:
	return (1);			/* failure */
}