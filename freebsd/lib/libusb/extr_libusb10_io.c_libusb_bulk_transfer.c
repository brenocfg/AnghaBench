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
typedef  int /*<<< orphan*/  libusb_device_handle ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_FUNCTION ; 
 int /*<<< orphan*/  LIBUSB_TRANSFER_TYPE_BULK ; 
 int libusb10_do_transfer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * libusb10_get_context_by_device_handle (int /*<<< orphan*/ *) ; 

int
libusb_bulk_transfer(libusb_device_handle *devh,
    uint8_t endpoint, uint8_t *data, int length,
    int *transferred, unsigned int timeout)
{
	libusb_context *ctx;
	int ret;

	ctx = libusb10_get_context_by_device_handle(devh);

	DPRINTF(ctx, LIBUSB_DEBUG_FUNCTION, "libusb_bulk_transfer enter");

	ret = libusb10_do_transfer(devh, endpoint, data, length, transferred,
	    timeout, LIBUSB_TRANSFER_TYPE_BULK);

	DPRINTF(ctx, LIBUSB_DEBUG_FUNCTION, "libusb_bulk_transfer leave");
	return (ret);
}