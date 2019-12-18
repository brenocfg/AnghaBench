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
struct udl_softc {int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_cmd_buf_free; int /*<<< orphan*/  sc_cmd_buf_pending; } ;
struct udl_cmd_head {int dummy; } ;
struct udl_cmd_buf {int /*<<< orphan*/  off; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_CONCAT (int /*<<< orphan*/ *,struct udl_cmd_head*,int /*<<< orphan*/ ) ; 
 struct udl_cmd_buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct udl_cmd_head*,struct udl_cmd_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct udl_cmd_buf*,int /*<<< orphan*/ ) ; 
 unsigned int UDL_CMD_MAX_FRAMES ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 struct udl_cmd_buf* udl_fb_synchronize_locked (struct udl_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct udl_cmd_head* usbd_xfer_get_priv (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,unsigned int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct udl_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
udl_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct udl_softc *sc = usbd_xfer_softc(xfer);
	struct udl_cmd_head *phead = usbd_xfer_get_priv(xfer);
	struct udl_cmd_buf *cb;
	unsigned i;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		TAILQ_CONCAT(&sc->sc_cmd_buf_free, phead, entry);
	case USB_ST_SETUP:
tr_setup:
		for (i = 0; i != UDL_CMD_MAX_FRAMES; i++) {
			cb = TAILQ_FIRST(&sc->sc_cmd_buf_pending);
			if (cb == NULL) {
				cb = udl_fb_synchronize_locked(sc);
				if (cb == NULL)
					break;
			} else {
				TAILQ_REMOVE(&sc->sc_cmd_buf_pending, cb, entry);
			}
			TAILQ_INSERT_TAIL(phead, cb, entry);
			usbd_xfer_set_frame_data(xfer, i, cb->buf, cb->off);
		}
		if (i != 0) {
			usbd_xfer_set_frames(xfer, i);
			usbd_transfer_submit(xfer);
		}
		break;
	default:
		TAILQ_CONCAT(&sc->sc_cmd_buf_free, phead, entry);
		if (error != USB_ERR_CANCELLED) {
			/* try clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
	/* wakeup any waiters */
	cv_signal(&sc->sc_cv);
}