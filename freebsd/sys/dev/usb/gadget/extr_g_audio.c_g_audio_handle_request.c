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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_device_request {scalar_t__ bmRequestType; int bRequest; } ;
struct g_audio_softc {int /*<<< orphan*/  sc_sample_rate; int /*<<< orphan*/  sc_volume_setting; int /*<<< orphan*/  sc_volume_limit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 scalar_t__ UT_READ_CLASS_INTERFACE ; 
 scalar_t__ UT_WRITE_CLASS_ENDPOINT ; 
 scalar_t__ UT_WRITE_CLASS_INTERFACE ; 
 struct g_audio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_audio_handle_request(device_t dev,
    const void *preq, void **pptr, uint16_t *plen,
    uint16_t offset, uint8_t *pstate)
{
	struct g_audio_softc *sc = device_get_softc(dev);
	const struct usb_device_request *req = preq;
	uint8_t is_complete = *pstate;

	if (!is_complete) {
		if ((req->bmRequestType == UT_READ_CLASS_INTERFACE) &&
		    (req->bRequest == 0x82 /* get min */ )) {

			if (offset == 0) {
				USETW(sc->sc_volume_limit, 0);
				*plen = 2;
				*pptr = &sc->sc_volume_limit;
			} else {
				*plen = 0;
			}
			return (0);
		} else if ((req->bmRequestType == UT_READ_CLASS_INTERFACE) &&
		    (req->bRequest == 0x83 /* get max */ )) {

			if (offset == 0) {
				USETW(sc->sc_volume_limit, 0x2000);
				*plen = 2;
				*pptr = &sc->sc_volume_limit;
			} else {
				*plen = 0;
			}
			return (0);
		} else if ((req->bmRequestType == UT_READ_CLASS_INTERFACE) &&
		    (req->bRequest == 0x84 /* get residue */ )) {

			if (offset == 0) {
				USETW(sc->sc_volume_limit, 1);
				*plen = 2;
				*pptr = &sc->sc_volume_limit;
			} else {
				*plen = 0;
			}
			return (0);
		} else if ((req->bmRequestType == UT_READ_CLASS_INTERFACE) &&
		    (req->bRequest == 0x81 /* get value */ )) {

			if (offset == 0) {
				USETW(sc->sc_volume_setting, 0x2000);
				*plen = sizeof(sc->sc_volume_setting);
				*pptr = &sc->sc_volume_setting;
			} else {
				*plen = 0;
			}
			return (0);
		} else if ((req->bmRequestType == UT_WRITE_CLASS_INTERFACE) &&
		    (req->bRequest == 0x01 /* set value */ )) {

			if (offset == 0) {
				*plen = sizeof(sc->sc_volume_setting);
				*pptr = &sc->sc_volume_setting;
			} else {
				*plen = 0;
			}
			return (0);
		} else if ((req->bmRequestType == UT_WRITE_CLASS_ENDPOINT) &&
		    (req->bRequest == 0x01 /* set value */ )) {

			if (offset == 0) {
				*plen = sizeof(sc->sc_sample_rate);
				*pptr = &sc->sc_sample_rate;
			} else {
				*plen = 0;
			}
			return (0);
		}
	}
	return (ENXIO);			/* use builtin handler */
}