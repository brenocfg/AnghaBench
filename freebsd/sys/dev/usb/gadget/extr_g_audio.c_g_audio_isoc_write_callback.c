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
struct g_audio_softc {int sc_throughput; int** sc_data_len; int /*<<< orphan*/  sc_mode; int /*<<< orphan*/ ** sc_data_buf; struct usb_xfer** sc_xfer; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int G_AUDIO_BUFSIZE ; 
 int G_AUDIO_FRAMES ; 
 size_t G_AUDIO_ISOC0_WR ; 
 int /*<<< orphan*/  G_AUDIO_MODE_LOOP ; 
 int /*<<< orphan*/  G_AUDIO_MODE_PATTERN ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  g_audio_make_samples (struct g_audio_softc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct g_audio_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_audio_isoc_write_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct g_audio_softc *sc = usbd_xfer_softc(xfer);
	int actlen;
	int aframes;
	int nr = (xfer == sc->sc_xfer[G_AUDIO_ISOC0_WR]) ? 0 : 1;
	int16_t *ptr;
	int i;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	DPRINTF("st=%d aframes=%d actlen=%d bytes\n",
	    USB_GET_STATE(xfer), aframes, actlen);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:

		sc->sc_throughput += actlen;

		if (sc->sc_mode == G_AUDIO_MODE_LOOP)
			break;		/* sync with RX */

	case USB_ST_SETUP:
tr_setup:

		ptr = sc->sc_data_buf[nr];

		if (sc->sc_mode == G_AUDIO_MODE_PATTERN) {

			for (i = 0; i != G_AUDIO_FRAMES; i++) {

				usbd_xfer_set_frame_data(xfer, i, ptr, sc->sc_data_len[nr][i]);

				g_audio_make_samples(sc, ptr, (G_AUDIO_BUFSIZE / G_AUDIO_FRAMES) / 2);

				ptr += (G_AUDIO_BUFSIZE / G_AUDIO_FRAMES) / 2;
			}
		} else if (sc->sc_mode == G_AUDIO_MODE_LOOP) {

			for (i = 0; i != G_AUDIO_FRAMES; i++) {

				usbd_xfer_set_frame_data(xfer, i, ptr, sc->sc_data_len[nr][i] & ~3);

				g_audio_make_samples(sc, ptr, sc->sc_data_len[nr][i] / 4);

				ptr += (G_AUDIO_BUFSIZE / G_AUDIO_FRAMES) / 2;
			}
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