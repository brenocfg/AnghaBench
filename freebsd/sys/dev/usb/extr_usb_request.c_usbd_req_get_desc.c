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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  UR_GET_DESCRIPTOR ; 
 scalar_t__ USB_ERR_INVAL ; 
 scalar_t__ USB_ERR_TIMEOUT ; 
 int /*<<< orphan*/  USB_SHORT_XFER_OK ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UT_READ_DEVICE ; 
 int hz ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (struct mtx*,int) ; 
 scalar_t__ usbd_do_request_flags (struct usb_device*,struct mtx*,struct usb_device_request*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

usb_error_t
usbd_req_get_desc(struct usb_device *udev,
    struct mtx *mtx, uint16_t *actlen, void *desc,
    uint16_t min_len, uint16_t max_len,
    uint16_t id, uint8_t type, uint8_t index,
    uint8_t retries)
{
	struct usb_device_request req;
	uint8_t *buf = desc;
	usb_error_t err;

	DPRINTFN(4, "id=%d, type=%d, index=%d, max_len=%d\n",
	    id, type, index, max_len);

	req.bmRequestType = UT_READ_DEVICE;
	req.bRequest = UR_GET_DESCRIPTOR;
	USETW2(req.wValue, type, index);
	USETW(req.wIndex, id);

	while (1) {

		if ((min_len < 2) || (max_len < 2)) {
			err = USB_ERR_INVAL;
			goto done;
		}
		USETW(req.wLength, min_len);

		err = usbd_do_request_flags(udev, mtx, &req,
		    desc, 0, NULL, 500 /* ms */);

		if (err != 0 && err != USB_ERR_TIMEOUT &&
		    min_len != max_len) {
			/* clear descriptor data */
			memset(desc, 0, max_len);

			/* try to read full descriptor length */
			USETW(req.wLength, max_len);

			err = usbd_do_request_flags(udev, mtx, &req,
			    desc, USB_SHORT_XFER_OK, NULL, 500 /* ms */);

			if (err == 0) {
				/* verify length */
				if (buf[0] > max_len)
					buf[0] = max_len;
				else if (buf[0] < 2)
					err = USB_ERR_INVAL;

				min_len = buf[0];

				/* enforce descriptor type */
				buf[1] = type;
				goto done;
			}
		}

		if (err) {
			if (!retries) {
				goto done;
			}
			retries--;

			usb_pause_mtx(mtx, hz / 5);

			continue;
		}

		if (min_len == max_len) {

			/* enforce correct length */
			if ((buf[0] > min_len) && (actlen == NULL))
				buf[0] = min_len;

			/* enforce correct type */
			buf[1] = type;

			goto done;
		}
		/* range check */

		if (max_len > buf[0]) {
			max_len = buf[0];
		}
		/* zero minimum data */

		while (min_len > max_len) {
			min_len--;
			buf[min_len] = 0;
		}

		/* set new minimum length */

		min_len = max_len;
	}
done:
	if (actlen != NULL) {
		if (err)
			*actlen = 0;
		else
			*actlen = min_len;
	}
	return (err);
}