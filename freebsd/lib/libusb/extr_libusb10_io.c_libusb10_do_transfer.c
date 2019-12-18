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
typedef  int /*<<< orphan*/  uint8_t ;
struct libusb_transfer {int type; unsigned int timeout; int length; int actual_length; int status; int /*<<< orphan*/  callback; void* user_data; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  endpoint; int /*<<< orphan*/ * dev_handle; } ;
typedef  int /*<<< orphan*/  libusb_device_handle ;
typedef  int /*<<< orphan*/  libusb_context ;
struct TYPE_2__ {int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NO_DEVICE ; 
 int LIBUSB_ERROR_NO_MEM ; 
 int LIBUSB_ERROR_OTHER ; 
 int LIBUSB_ERROR_OVERFLOW ; 
 int LIBUSB_ERROR_PIPE ; 
 int LIBUSB_ERROR_TIMEOUT ; 
#define  LIBUSB_TRANSFER_COMPLETED 132 
#define  LIBUSB_TRANSFER_NO_DEVICE 131 
#define  LIBUSB_TRANSFER_OVERFLOW 130 
#define  LIBUSB_TRANSFER_STALL 129 
#define  LIBUSB_TRANSFER_TIMED_OUT 128 
 int /*<<< orphan*/  libusb10_do_transfer_cb ; 
 struct libusb_transfer* libusb_alloc_transfer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_cancel_transfer (struct libusb_transfer*) ; 
 int /*<<< orphan*/  libusb_free_transfer (struct libusb_transfer*) ; 
 TYPE_1__* libusb_get_device (int /*<<< orphan*/ *) ; 
 int libusb_handle_events (int /*<<< orphan*/ *) ; 
 int libusb_submit_transfer (struct libusb_transfer*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int
libusb10_do_transfer(libusb_device_handle *devh,
    uint8_t endpoint, uint8_t *data, int length,
    int *transferred, unsigned int timeout, int type)
{
	libusb_context *ctx;
	struct libusb_transfer *xfer;
	int done;
	int ret;

	if (devh == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if ((length != 0) && (data == NULL))
		return (LIBUSB_ERROR_INVALID_PARAM);

	xfer = libusb_alloc_transfer(0);
	if (xfer == NULL)
		return (LIBUSB_ERROR_NO_MEM);

	ctx = libusb_get_device(devh)->ctx;

	xfer->dev_handle = devh;
	xfer->endpoint = endpoint;
	xfer->type = type;
	xfer->timeout = timeout;
	xfer->buffer = data;
	xfer->length = length;
	xfer->user_data = (void *)&done;
	xfer->callback = libusb10_do_transfer_cb;
	done = 0;

	if ((ret = libusb_submit_transfer(xfer)) < 0) {
		libusb_free_transfer(xfer);
		return (ret);
	}
	while (done == 0) {
		if ((ret = libusb_handle_events(ctx)) < 0) {
			libusb_cancel_transfer(xfer);
			usleep(1000);	/* nice it */
		}
	}

	*transferred = xfer->actual_length;

	switch (xfer->status) {
	case LIBUSB_TRANSFER_COMPLETED:
		ret = 0;
		break;
	case LIBUSB_TRANSFER_TIMED_OUT:
		ret = LIBUSB_ERROR_TIMEOUT;
		break;
	case LIBUSB_TRANSFER_OVERFLOW:
		ret = LIBUSB_ERROR_OVERFLOW;
		break;
	case LIBUSB_TRANSFER_STALL:
		ret = LIBUSB_ERROR_PIPE;
		break;
	case LIBUSB_TRANSFER_NO_DEVICE:
		ret = LIBUSB_ERROR_NO_DEVICE;
		break;
	default:
		ret = LIBUSB_ERROR_OTHER;
		break;
	}

	libusb_free_transfer(xfer);
	return (ret);
}