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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fp; } ;
struct umidi_sub_chan {TYPE_1__ fifo; int /*<<< orphan*/  read_open; } ;
struct umidi_chan {int max_emb_jack; struct umidi_sub_chan* sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 size_t USB_FIFO_RX ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int* umidi_cmd_to_len ; 
 int /*<<< orphan*/  usb_fifo_put_data_linear (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int,int*,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct umidi_chan* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
umidi_bulk_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umidi_chan *chan = usbd_xfer_softc(xfer);
	struct umidi_sub_chan *sub;
	struct usb_page_cache *pc;
	uint8_t buf[4];
	uint8_t cmd_len;
	uint8_t cn;
	uint16_t pos;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		DPRINTF("actlen=%d bytes\n", actlen);

		pos = 0;
		pc = usbd_xfer_get_frame(xfer, 0);

		while (actlen >= 4) {

			/* copy out the MIDI data */
			usbd_copy_out(pc, pos, buf, 4);
			/* command length */
			cmd_len = umidi_cmd_to_len[buf[0] & 0xF];
			/* cable number */
			cn = buf[0] >> 4;
			/*
			 * Lookup sub-channel. The index is range
			 * checked below.
			 */
			sub = &chan->sub[cn];

			if ((cmd_len != 0) && (cn < chan->max_emb_jack) &&
			    (sub->read_open != 0)) {

				/* Send data to the application */
				usb_fifo_put_data_linear(
				    sub->fifo.fp[USB_FIFO_RX],
				    buf + 1, cmd_len, 1);
			}
			actlen -= 4;
			pos += 4;
		}

	case USB_ST_SETUP:
		DPRINTF("start\n");
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;

	default:
		DPRINTF("error=%s\n", usbd_errstr(error));

		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}