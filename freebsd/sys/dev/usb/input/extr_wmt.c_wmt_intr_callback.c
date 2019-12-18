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
typedef  int /*<<< orphan*/  uint8_t ;
struct wmt_softc {int isize; int /*<<< orphan*/  report_id; int /*<<< orphan*/ * buf; } ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,struct wmt_softc*,int) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct wmt_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmt_process_report (struct wmt_softc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
wmt_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct wmt_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint8_t *buf = sc->buf;
	int len;

	usbd_xfer_status(xfer, &len, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		pc = usbd_xfer_get_frame(xfer, 0);

		DPRINTFN(6, "sc=%p actlen=%d\n", sc, len);

		if (len >= (int)sc->isize || (len > 0 && sc->report_id != 0)) {
			/* Limit report length to the maximum */
			if (len > (int)sc->isize)
				len = sc->isize;

			usbd_copy_out(pc, 0, buf, len);

			/* Ignore irrelevant reports */
			if (sc->report_id && *buf != sc->report_id)
				goto tr_ignore;

			/* Make sure we don't process old data */
			if (len < sc->isize)
				bzero(buf + len, sc->isize - len);

			/* Strip leading "report ID" byte */
			if (sc->report_id) {
				len--;
				buf++;
			}

			wmt_process_report(sc, buf, len);
		} else {
tr_ignore:
			DPRINTF("Ignored transfer, %d bytes\n", len);
		}

	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;
	default:
		if (error != USB_ERR_CANCELLED) {
			/* Try clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}