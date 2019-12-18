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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_xfer {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  volume_down_loc; int /*<<< orphan*/  volume_down_id; int /*<<< orphan*/  volume_up_loc; int /*<<< orphan*/  volume_up_id; int /*<<< orphan*/  mute_loc; int /*<<< orphan*/  mute_id; } ;
struct uaudio_softc {TYPE_1__ sc_hid; struct snd_mixer* sc_mixer_dev; } ;
struct snd_mixer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int UAUDIO_HID_HAS_ID ; 
 int UAUDIO_HID_HAS_MUTE ; 
 int UAUDIO_HID_HAS_VOLUME_DOWN ; 
 int UAUDIO_HID_HAS_VOLUME_UP ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  hid_get_data (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixer_hwvol_mute_locked (struct snd_mixer*) ; 
 int /*<<< orphan*/  mixer_hwvol_step_locked (struct snd_mixer*,int,int) ; 
 int usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/ * usbd_xfer_get_frame_buffer (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct uaudio_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uaudio_hid_rx_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct uaudio_softc *sc = usbd_xfer_softc(xfer);
	const uint8_t *buffer = usbd_xfer_get_frame_buffer(xfer, 0);
	struct snd_mixer *m;
	uint8_t id;
	int actlen;

	usbd_xfer_status(xfer, &actlen, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		DPRINTF("actlen=%d\n", actlen);

		if (actlen != 0 &&
		    (sc->sc_hid.flags & UAUDIO_HID_HAS_ID)) {
			id = *buffer;
			buffer++;
			actlen--;
		} else {
			id = 0;
		}

		m = sc->sc_mixer_dev;

		if ((sc->sc_hid.flags & UAUDIO_HID_HAS_MUTE) &&
		    (sc->sc_hid.mute_id == id) &&
		    hid_get_data(buffer, actlen,
		    &sc->sc_hid.mute_loc)) {

			DPRINTF("Mute toggle\n");

			mixer_hwvol_mute_locked(m);
		}

		if ((sc->sc_hid.flags & UAUDIO_HID_HAS_VOLUME_UP) &&
		    (sc->sc_hid.volume_up_id == id) &&
		    hid_get_data(buffer, actlen,
		    &sc->sc_hid.volume_up_loc)) {

			DPRINTF("Volume Up\n");

			mixer_hwvol_step_locked(m, 1, 1);
		}

		if ((sc->sc_hid.flags & UAUDIO_HID_HAS_VOLUME_DOWN) &&
		    (sc->sc_hid.volume_down_id == id) &&
		    hid_get_data(buffer, actlen,
		    &sc->sc_hid.volume_down_loc)) {

			DPRINTF("Volume Down\n");

			mixer_hwvol_step_locked(m, -1, -1);
		}

	case USB_ST_SETUP:
tr_setup:
		/* check if we can put more data into the FIFO */
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
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