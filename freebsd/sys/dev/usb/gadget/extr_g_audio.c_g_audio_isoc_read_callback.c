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
struct g_audio_softc {int sc_throughput; int /*<<< orphan*/ ** sc_data_buf; struct usb_xfer** sc_xfer; int /*<<< orphan*/ ** sc_data_len; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int G_AUDIO_BUFSIZE ; 
 int G_AUDIO_FRAMES ; 
 size_t G_AUDIO_ISOC0_RD ; 
 size_t G_AUDIO_ISOC0_WR ; 
 size_t G_AUDIO_ISOC1_WR ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_frame_len (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct g_audio_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_audio_isoc_read_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct g_audio_softc *sc = usbd_xfer_softc(xfer);
	int actlen;
	int aframes;
	int nr = (xfer == sc->sc_xfer[G_AUDIO_ISOC0_RD]) ? 0 : 1;
	int16_t *ptr;
	int i;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	DPRINTF("st=%d aframes=%d actlen=%d bytes\n",
	    USB_GET_STATE(xfer), aframes, actlen);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		sc->sc_throughput += actlen;

		for (i = 0; i != G_AUDIO_FRAMES; i++) {
			sc->sc_data_len[nr][i] = usbd_xfer_frame_len(xfer, i);
		}

		usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC0_WR]);
		usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC1_WR]);

		break;

	case USB_ST_SETUP:
tr_setup:
		ptr = sc->sc_data_buf[nr];

		for (i = 0; i != G_AUDIO_FRAMES; i++) {

			usbd_xfer_set_frame_data(xfer, i, ptr,
			    G_AUDIO_BUFSIZE / G_AUDIO_FRAMES);

			ptr += (G_AUDIO_BUFSIZE / G_AUDIO_FRAMES) / 2;
		}

		usbd_transfer_submit(xfer);
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