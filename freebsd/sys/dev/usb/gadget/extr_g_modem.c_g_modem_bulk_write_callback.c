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
struct g_modem_softc {int sc_throughput; int sc_tx_interval; int sc_pattern_len; int* sc_data_buf; int* sc_pattern; int sc_data_len; int /*<<< orphan*/  sc_tx_busy; int /*<<< orphan*/  sc_mode; int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int G_MODEM_BUFSIZE ; 
 size_t G_MODEM_BULK_RD ; 
 int /*<<< orphan*/  G_MODEM_MODE_LOOP ; 
 int /*<<< orphan*/  G_MODEM_MODE_PATTERN ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_interval (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct g_modem_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_modem_bulk_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct g_modem_softc *sc = usbd_xfer_softc(xfer);
	int actlen;
	int aframes;
	int mod;
	int x;
	int max;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	DPRINTF("st=%d aframes=%d actlen=%d bytes\n",
	    USB_GET_STATE(xfer), aframes, actlen);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		sc->sc_tx_busy = 0;
		sc->sc_throughput += actlen;

		if (sc->sc_mode == G_MODEM_MODE_LOOP) {
			/* start loop */
			usbd_transfer_start(sc->sc_xfer[G_MODEM_BULK_RD]);
			break;
		} else if ((sc->sc_mode == G_MODEM_MODE_PATTERN) && (sc->sc_tx_interval != 0)) {
			/* wait for next timeout */
			break;
		}
	case USB_ST_SETUP:
tr_setup:
		if (sc->sc_mode == G_MODEM_MODE_PATTERN) {

			mod = sc->sc_pattern_len;
			max = sc->sc_tx_interval ? mod : G_MODEM_BUFSIZE;

			if (mod == 0) {
				for (x = 0; x != max; x++)
					sc->sc_data_buf[x] = x % 255;
			} else {
				for (x = 0; x != max; x++)
					sc->sc_data_buf[x] = sc->sc_pattern[x % mod];
			}

			usbd_xfer_set_frame_data(xfer, 0, sc->sc_data_buf, max);
			usbd_xfer_set_interval(xfer, 0);
			usbd_xfer_set_frames(xfer, 1);
			usbd_transfer_submit(xfer);

		} else if (sc->sc_mode == G_MODEM_MODE_LOOP) {

			if (sc->sc_tx_busy == 0)
				break;

			x = sc->sc_tx_interval;

			if (x < 0)
				x = 0;
			else if (x > 256)
				x = 256;

			usbd_xfer_set_frame_data(xfer, 0, sc->sc_data_buf, sc->sc_data_len);
			usbd_xfer_set_interval(xfer, x);
			usbd_xfer_set_frames(xfer, 1);
			usbd_transfer_submit(xfer);
		} else {
			sc->sc_tx_busy = 0;
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