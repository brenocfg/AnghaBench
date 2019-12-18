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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fp; } ;
struct umidi_sub_chan {int /*<<< orphan*/ * temp_cmd; TYPE_1__ fifo; int /*<<< orphan*/  write_open; } ;
struct umidi_chan {int curr_cable; size_t max_emb_jack; int /*<<< orphan*/  single_command; struct umidi_sub_chan* sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int UMIDI_TX_FRAMES ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 size_t USB_FIFO_TX ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  umidi_convert_to_usb (struct umidi_sub_chan*,size_t,int) ; 
 int /*<<< orphan*/  usb_fifo_get_data_linear (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_in (struct usb_page_cache*,int,int /*<<< orphan*/ *,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct umidi_chan* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
umidi_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umidi_chan *chan = usbd_xfer_softc(xfer);
	struct umidi_sub_chan *sub;
	struct usb_page_cache *pc;
	uint32_t actlen;
	uint16_t nframes;
	uint8_t buf;
	uint8_t start_cable;
	uint8_t tr_any;
	int len;

	usbd_xfer_status(xfer, &len, NULL, NULL, NULL);

	/*
	 * NOTE: Some MIDI devices only accept 4 bytes of data per
	 * short terminated USB transfer.
	 */
	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTF("actlen=%d bytes\n", len);

	case USB_ST_SETUP:
tr_setup:
		DPRINTF("start\n");

		nframes = 0;	/* reset */
		start_cable = chan->curr_cable;
		tr_any = 0;
		pc = usbd_xfer_get_frame(xfer, 0);

		while (1) {

			/* round robin de-queueing */

			sub = &chan->sub[chan->curr_cable];

			if (sub->write_open) {
				usb_fifo_get_data_linear(sub->fifo.fp[USB_FIFO_TX],
				    &buf, 1, &actlen, 0);
			} else {
				actlen = 0;
			}

			if (actlen) {

				tr_any = 1;

				DPRINTF("byte=0x%02x from FIFO %u\n", buf,
				    (unsigned int)chan->curr_cable);

				if (umidi_convert_to_usb(sub, chan->curr_cable, buf)) {

					DPRINTF("sub=0x%02x 0x%02x 0x%02x 0x%02x\n",
					    sub->temp_cmd[0], sub->temp_cmd[1],
					    sub->temp_cmd[2], sub->temp_cmd[3]);

					usbd_copy_in(pc, nframes * 4, sub->temp_cmd, 4);

					nframes++;

					if ((nframes >= UMIDI_TX_FRAMES) || (chan->single_command != 0))
						break;
				} else {
					continue;
				}
			}

			chan->curr_cable++;
			if (chan->curr_cable >= chan->max_emb_jack)
				chan->curr_cable = 0;

			if (chan->curr_cable == start_cable) {
				if (tr_any == 0)
					break;
				tr_any = 0;
			}
		}

		if (nframes != 0) {
			DPRINTF("Transferring %d frames\n", (int)nframes);
			usbd_xfer_set_frame_len(xfer, 0, 4 * nframes);
			usbd_transfer_submit(xfer);
		}
		break;

	default:			/* Error */

		DPRINTF("error=%s\n", usbd_errstr(error));

		if (error != USB_ERR_CANCELLED) {
			/* try to clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}