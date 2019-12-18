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
typedef  int /*<<< orphan*/  uint32_t ;
struct libusb_transfer {int /*<<< orphan*/  callback; void* user_data; scalar_t__ length; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  timeout; int /*<<< orphan*/  type; scalar_t__ endpoint; int /*<<< orphan*/ * dev_handle; } ;
struct libusb_control_setup {int /*<<< orphan*/  wLength; } ;
typedef  int /*<<< orphan*/  libusb_transfer_cb_fn ;
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 scalar_t__ LIBUSB_CONTROL_SETUP_SIZE ; 
 int /*<<< orphan*/  LIBUSB_TRANSFER_TYPE_CONTROL ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 

void
libusb_fill_control_transfer(struct libusb_transfer *transfer, 
    libusb_device_handle *devh, uint8_t *buf,
    libusb_transfer_cb_fn callback, void *user_data,
    uint32_t timeout)
{
	struct libusb_control_setup *setup = (struct libusb_control_setup *)buf;

	transfer->dev_handle = devh;
	transfer->endpoint = 0;
	transfer->type = LIBUSB_TRANSFER_TYPE_CONTROL;
	transfer->timeout = timeout;
	transfer->buffer = buf;
	if (setup != NULL)
		transfer->length = LIBUSB_CONTROL_SETUP_SIZE
			+ le16toh(setup->wLength);
	else
		transfer->length = 0;
	transfer->user_data = user_data;
	transfer->callback = callback;

}