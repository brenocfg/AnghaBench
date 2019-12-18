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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct usb_device {int dummy; } ;
struct uaudio_softc {int sc_sndstat_valid; int /*<<< orphan*/  sc_sndstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_AUTOEXTEND ; 
 int UAUDIO_CHANNELS_MAX ; 
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  sbuf_finish (int /*<<< orphan*/ *) ; 
 scalar_t__ sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uaudio_chan_fill_info_sub (struct uaudio_softc*,struct usb_device*,scalar_t__,int,int) ; 
 int uaudio_default_bits ; 
 int uaudio_default_channels ; 
 scalar_t__ uaudio_default_rate ; 
 scalar_t__* uaudio_rate_list ; 
 int usbd_get_speed (struct usb_device*) ; 

__attribute__((used)) static void
uaudio_chan_fill_info(struct uaudio_softc *sc, struct usb_device *udev)
{
	uint32_t rate = uaudio_default_rate;
	uint8_t z;
	uint8_t bits = uaudio_default_bits;
	uint8_t y;
	uint8_t channels = uaudio_default_channels;
	uint8_t x;

	bits -= (bits % 8);
	if ((bits == 0) || (bits > 32)) {
		/* set a valid value */
		bits = 32;
	}
	if (channels == 0) {
		switch (usbd_get_speed(udev)) {
		case USB_SPEED_LOW:
		case USB_SPEED_FULL:
			/*
			 * Due to high bandwidth usage and problems
			 * with HIGH-speed split transactions we
			 * disable surround setups on FULL-speed USB
			 * by default
			 */
			channels = 4;
			break;
		default:
			channels = UAUDIO_CHANNELS_MAX;
			break;
		}
	} else if (channels > UAUDIO_CHANNELS_MAX)
		channels = UAUDIO_CHANNELS_MAX;

	if (sbuf_new(&sc->sc_sndstat, NULL, 4096, SBUF_AUTOEXTEND))
		sc->sc_sndstat_valid = 1;

	/* try to search for a valid config */

	for (x = channels; x; x--) {
		for (y = bits; y; y -= 8) {

			/* try user defined rate, if any */
			if (rate != 0)
				uaudio_chan_fill_info_sub(sc, udev, rate, x, y);

			/* try find a matching rate, if any */
			for (z = 0; uaudio_rate_list[z]; z++)
				uaudio_chan_fill_info_sub(sc, udev, uaudio_rate_list[z], x, y);
		}
	}
	if (sc->sc_sndstat_valid)
		sbuf_finish(&sc->sc_sndstat);
}