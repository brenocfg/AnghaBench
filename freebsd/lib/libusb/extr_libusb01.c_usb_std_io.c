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
typedef  int /*<<< orphan*/  usb_dev_handle ;
typedef  int uint32_t ;
struct libusb20_transfer {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIMEDOUT ; 
#define  LIBUSB20_TRANSFER_TIMED_OUT 128 
 scalar_t__ libusb20_dev_process (void*) ; 
 int /*<<< orphan*/  libusb20_dev_wait_process (void*,int) ; 
 int libusb20_tr_get_actual_length (struct libusb20_transfer*) ; 
 int libusb20_tr_get_max_total_length (struct libusb20_transfer*) ; 
 int libusb20_tr_get_status (struct libusb20_transfer*) ; 
 scalar_t__ libusb20_tr_pending (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_setup_bulk (struct libusb20_transfer*,char*,int,int) ; 
 int /*<<< orphan*/  libusb20_tr_setup_intr (struct libusb20_transfer*,char*,int,int) ; 
 int /*<<< orphan*/  libusb20_tr_start (struct libusb20_transfer*) ; 
 struct libusb20_transfer* usb_get_transfer_by_ep_no (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
usb_std_io(usb_dev_handle * dev, int ep, char *bytes, int size,
    int timeout, int is_intr)
{
	struct libusb20_transfer *xfer;
	uint32_t temp;
	uint32_t maxsize;
	uint32_t actlen;
	char *oldbytes;

	xfer = usb_get_transfer_by_ep_no(dev, ep);
	if (xfer == NULL)
		return (-1);

	if (libusb20_tr_pending(xfer)) {
		/* there is already a transfer ongoing */
		return (-1);
	}
	maxsize = libusb20_tr_get_max_total_length(xfer);
	oldbytes = bytes;

	/*
	 * We allow transferring zero bytes which is the same
	 * equivalent to a zero length USB packet.
	 */
	do {

		temp = size;
		if (temp > maxsize) {
			/* find maximum possible length */
			temp = maxsize;
		}
		if (is_intr)
			libusb20_tr_setup_intr(xfer, bytes, temp, timeout);
		else
			libusb20_tr_setup_bulk(xfer, bytes, temp, timeout);

		libusb20_tr_start(xfer);

		while (1) {

			if (libusb20_dev_process((void *)dev) != 0) {
				/* device detached */
				return (-1);
			}
			if (libusb20_tr_pending(xfer) == 0) {
				/* transfer complete */
				break;
			}
			/* wait for USB event from kernel */
			libusb20_dev_wait_process((void *)dev, -1);
		}

		switch (libusb20_tr_get_status(xfer)) {
		case 0:
			/* success */
			break;
		case LIBUSB20_TRANSFER_TIMED_OUT:
			/* transfer timeout */
			return (-ETIMEDOUT);
		default:
			/* other transfer error */
			return (-ENXIO);
		}
		actlen = libusb20_tr_get_actual_length(xfer);

		bytes += actlen;
		size -= actlen;

		if (actlen != temp) {
			/* short transfer */
			break;
		}
	} while (size > 0);

	return (bytes - oldbytes);
}