#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct g_keyboard_softc {int sc_state; TYPE_1__* sc_data; int /*<<< orphan*/  sc_mode; } ;
struct TYPE_3__ {void** keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int G_KEYBOARD_MAX_STRLEN ; 
 int /*<<< orphan*/  G_KEYBOARD_MODE_PATTERN ; 
 int /*<<< orphan*/  G_KEYBOARD_MODE_SILENT ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 void* g_keyboard_get_keycode (struct g_keyboard_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_data (struct usb_xfer*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_frames (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct g_keyboard_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_keyboard_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct g_keyboard_softc *sc = usbd_xfer_softc(xfer);
	int actlen;
	int aframes;

	usbd_xfer_status(xfer, &actlen, NULL, &aframes, NULL);

	DPRINTF("st=%d aframes=%d actlen=%d bytes\n",
	    USB_GET_STATE(xfer), aframes, actlen);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		break;

	case USB_ST_SETUP:
tr_setup:
		if (sc->sc_mode == G_KEYBOARD_MODE_SILENT) {
			memset(&sc->sc_data, 0, sizeof(sc->sc_data));
			usbd_xfer_set_frame_data(xfer, 0, &sc->sc_data[0], sizeof(sc->sc_data[0]));
			usbd_xfer_set_frame_data(xfer, 1, &sc->sc_data[1], sizeof(sc->sc_data[1]));
			usbd_xfer_set_frames(xfer, 2);
			usbd_transfer_submit(xfer);

		} else if (sc->sc_mode == G_KEYBOARD_MODE_PATTERN) {

			memset(&sc->sc_data, 0, sizeof(sc->sc_data));

			if ((sc->sc_state < 0) || (sc->sc_state >= G_KEYBOARD_MAX_STRLEN))
				sc->sc_state = 0;

			switch (sc->sc_state % 6) {
			case 0:
				sc->sc_data[0].keycode[0] =
				    g_keyboard_get_keycode(sc, sc->sc_state + 0);
			case 1:
				sc->sc_data[0].keycode[1] =
				    g_keyboard_get_keycode(sc, sc->sc_state + 1);
			case 2:
				sc->sc_data[0].keycode[2] =
				    g_keyboard_get_keycode(sc, sc->sc_state + 2);
			case 3:
				sc->sc_data[0].keycode[3] =
				    g_keyboard_get_keycode(sc, sc->sc_state + 3);
			case 4:
				sc->sc_data[0].keycode[4] =
				    g_keyboard_get_keycode(sc, sc->sc_state + 4);
			default:
				sc->sc_data[0].keycode[5] =
				    g_keyboard_get_keycode(sc, sc->sc_state + 5);
			}

			sc->sc_state++;

			usbd_xfer_set_frame_data(xfer, 0, &sc->sc_data[0], sizeof(sc->sc_data[0]));
			usbd_xfer_set_frame_data(xfer, 1, &sc->sc_data[1], sizeof(sc->sc_data[1]));
			usbd_xfer_set_frames(xfer, 2);
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