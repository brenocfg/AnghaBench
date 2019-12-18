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
typedef  int uint16_t ;
struct libusb20_device {int dummy; } ;
struct LIBUSB20_CONTROL_SETUP_DECODED {int bmRequestType; int wValue; int wIndex; int wLength; int /*<<< orphan*/  bRequest; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUSB20_CONTROL_SETUP ; 
 int LIBUSB20_DT_STRING ; 
 int LIBUSB20_ENDPOINT_IN ; 
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int LIBUSB20_ERROR_OTHER ; 
 int /*<<< orphan*/  LIBUSB20_INIT (int /*<<< orphan*/ ,struct LIBUSB20_CONTROL_SETUP_DECODED*) ; 
 int LIBUSB20_RECIPIENT_DEVICE ; 
 int /*<<< orphan*/  LIBUSB20_REQUEST_GET_DESCRIPTOR ; 
 int LIBUSB20_REQUEST_TYPE_STANDARD ; 
 int LIBUSB20_TRANSFER_SINGLE_SHORT_NOT_OK ; 
 int libusb20_dev_request_sync (struct libusb20_device*,struct LIBUSB20_CONTROL_SETUP_DECODED*,void*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

int
libusb20_dev_req_string_sync(struct libusb20_device *pdev,
    uint8_t str_index, uint16_t langid, void *ptr, uint16_t len)
{
	struct LIBUSB20_CONTROL_SETUP_DECODED req;
	int error;
	int flags;

	/* make sure memory is initialised */
	memset(ptr, 0, len);

	if (len < 4) {
		/* invalid length */
		return (LIBUSB20_ERROR_INVALID_PARAM);
	}
	LIBUSB20_INIT(LIBUSB20_CONTROL_SETUP, &req);

	/*
	 * We need to read the USB string in two steps else some USB
	 * devices will complain.
	 */
	req.bmRequestType =
	    LIBUSB20_REQUEST_TYPE_STANDARD |
	    LIBUSB20_RECIPIENT_DEVICE |
	    LIBUSB20_ENDPOINT_IN;
	req.bRequest = LIBUSB20_REQUEST_GET_DESCRIPTOR;
	req.wValue = (LIBUSB20_DT_STRING << 8) | str_index;
	req.wIndex = langid;
	req.wLength = 4;		/* bytes */

	error = libusb20_dev_request_sync(pdev, &req,
	    ptr, NULL, 1000, LIBUSB20_TRANSFER_SINGLE_SHORT_NOT_OK);
	if (error) {
		/* try to request full string */
		req.wLength = 255;
		flags = 0;
	} else {
		/* extract length and request full string */
		req.wLength = *(uint8_t *)ptr;
		flags = LIBUSB20_TRANSFER_SINGLE_SHORT_NOT_OK;
	}
	if (req.wLength > len) {
		/* partial string read */
		req.wLength = len;
	}
	error = libusb20_dev_request_sync(pdev, &req, ptr, NULL, 1000, flags);
	if (error)
		return (error);

	if (((uint8_t *)ptr)[1] != LIBUSB20_DT_STRING)
		return (LIBUSB20_ERROR_OTHER);
	return (0);			/* success */
}