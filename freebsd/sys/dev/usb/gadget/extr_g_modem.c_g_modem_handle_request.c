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
struct usb_device_request {scalar_t__ bmRequestType; scalar_t__ bRequest; int* wValue; } ;
struct g_modem_softc {int /*<<< orphan*/  sc_abstract_state; int /*<<< orphan*/  sc_line_coding; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ UCDC_SEND_BREAK ; 
 scalar_t__ UCDC_SET_COMM_FEATURE ; 
 scalar_t__ UCDC_SET_CONTROL_LINE_STATE ; 
 scalar_t__ UCDC_SET_LINE_CODING ; 
 scalar_t__ UT_WRITE_CLASS_INTERFACE ; 
 struct g_modem_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_modem_handle_request(device_t dev,
    const void *preq, void **pptr, uint16_t *plen,
    uint16_t offset, uint8_t *pstate)
{
	struct g_modem_softc *sc = device_get_softc(dev);
	const struct usb_device_request *req = preq;
	uint8_t is_complete = *pstate;

	if (!is_complete) {
		if ((req->bmRequestType == UT_WRITE_CLASS_INTERFACE) &&
		    (req->bRequest == UCDC_SET_LINE_CODING) &&
		    (req->wValue[0] == 0x00) &&
		    (req->wValue[1] == 0x00)) {

			if (offset == 0) {
				*plen = sizeof(sc->sc_line_coding);
				*pptr = &sc->sc_line_coding;
			} else {
				*plen = 0;
			}
			return (0);
		} else if ((req->bmRequestType == UT_WRITE_CLASS_INTERFACE) &&
		    (req->bRequest == UCDC_SET_COMM_FEATURE)) {

			if (offset == 0) {
				*plen = sizeof(sc->sc_abstract_state);
				*pptr = &sc->sc_abstract_state;
			} else {
				*plen = 0;
			}
			return (0);
		} else if ((req->bmRequestType == UT_WRITE_CLASS_INTERFACE) &&
		    (req->bRequest == UCDC_SET_CONTROL_LINE_STATE)) {
			*plen = 0;
			return (0);
		} else if ((req->bmRequestType == UT_WRITE_CLASS_INTERFACE) &&
		    (req->bRequest == UCDC_SEND_BREAK)) {
			*plen = 0;
			return (0);
		}
	}
	return (ENXIO);			/* use builtin handler */
}