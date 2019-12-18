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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct ubt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBT_STAT_IERROR (struct ubt_softc*) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  ubt_isoc_read_one_frame (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_max_framelen (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int,int /*<<< orphan*/ ) ; 
 struct ubt_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
ubt_isoc_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ubt_softc	*sc = usbd_xfer_softc(xfer);
	int			n;
	int actlen, nframes;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, &nframes);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		for (n = 0; n < nframes; n ++)
			if (ubt_isoc_read_one_frame(xfer, n) < 0)
				break;
		/* FALLTHROUGH */

	case USB_ST_SETUP:
read_next:
		for (n = 0; n < nframes; n ++)
			usbd_xfer_set_frame_len(xfer, n,
			    usbd_xfer_max_framelen(xfer));

		usbd_transfer_submit(xfer);
		break;

	default: /* Error */
                if (error != USB_ERR_CANCELLED) {
                        UBT_STAT_IERROR(sc);
                        goto read_next;
                }

		/* transfer cancelled */
		break;
	}
}