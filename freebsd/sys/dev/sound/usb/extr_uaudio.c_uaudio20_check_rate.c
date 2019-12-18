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
typedef  scalar_t__ usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  UA20_CS_RANGE ; 
 int /*<<< orphan*/  UA20_CS_SAM_FREQ_CONTROL ; 
 int UAUDIO20_MAX_RATES ; 
 scalar_t__ UGETDW (int /*<<< orphan*/ *) ; 
 int UGETW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_DEFAULT_TIMEOUT ; 
 scalar_t__ USB_ERR_INVAL ; 
 int /*<<< orphan*/  USB_SHORT_XFER_OK ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 scalar_t__ usbd_do_request_flags (struct usb_device*,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
uaudio20_check_rate(struct usb_device *udev, uint8_t iface_no,
    uint8_t clockid, uint32_t rate)
{
	struct usb_device_request req;
	usb_error_t error;
#define	UAUDIO20_MAX_RATES 32	/* we support at maxium 32 rates */
	uint8_t data[2 + UAUDIO20_MAX_RATES * 12];
	uint16_t actlen;
	uint16_t rates;
	uint16_t x;

	DPRINTFN(6, "ifaceno=%d clockid=%d rate=%u\n",
	    iface_no, clockid, rate);

	req.bmRequestType = UT_READ_CLASS_INTERFACE;
	req.bRequest = UA20_CS_RANGE;
	USETW2(req.wValue, UA20_CS_SAM_FREQ_CONTROL, 0);
	USETW2(req.wIndex, clockid, iface_no);
	/*
	 * Assume there is at least one rate to begin with, else some
	 * devices might refuse to return the USB descriptor:
	 */
	USETW(req.wLength, (2 + 1 * 12));

	error = usbd_do_request_flags(udev, NULL, &req, data,
	    USB_SHORT_XFER_OK, &actlen, USB_DEFAULT_TIMEOUT);

	if (error != 0 || actlen < 2) {
		/*
		 * Likely the descriptor doesn't fit into the supplied
		 * buffer. Try using a larger buffer and see if that
		 * helps:
		 */
		rates = MIN(UAUDIO20_MAX_RATES, (255 - 2) / 12);
		error = USB_ERR_INVAL;
	} else {
		rates = UGETW(data);

		if (rates > UAUDIO20_MAX_RATES) {
			DPRINTF("Too many rates truncating to %d\n", UAUDIO20_MAX_RATES);
			rates = UAUDIO20_MAX_RATES;
			error = USB_ERR_INVAL;
		} else if (rates > 1) {
			DPRINTF("Need to read full rate descriptor\n");
			error = USB_ERR_INVAL;
		}
	}

	if (error != 0) {
		/*
		 * Try to read full rate descriptor.
		 */
		actlen = (2 + rates * 12);

		USETW(req.wLength, actlen);

	        error = usbd_do_request_flags(udev, NULL, &req, data,
		    USB_SHORT_XFER_OK, &actlen, USB_DEFAULT_TIMEOUT);
	
		if (error != 0 || actlen < 2)
			return (USB_ERR_INVAL);

		rates = UGETW(data);
	}

	actlen = (actlen - 2) / 12;

	if (rates > actlen) {
		DPRINTF("Too many rates truncating to %d\n", actlen);
		rates = actlen;
	}

	for (x = 0; x != rates; x++) {
		uint32_t min = UGETDW(data + 2 + (12 * x));
		uint32_t max = UGETDW(data + 6 + (12 * x));
		uint32_t res = UGETDW(data + 10 + (12 * x));

		if (res == 0) {
			DPRINTF("Zero residue\n");
			res = 1;
		}

		if (min > max) {
			DPRINTF("Swapped max and min\n");
			uint32_t temp;
			temp = min;
			min = max;
			max = temp;
		}

		if (rate >= min && rate <= max &&
		    (((rate - min) % res) == 0)) {
			return (0);
		}
	}
	return (USB_ERR_INVAL);
}