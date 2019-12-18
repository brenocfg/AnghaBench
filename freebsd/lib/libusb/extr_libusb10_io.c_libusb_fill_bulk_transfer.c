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
struct libusb_transfer {int length; int /*<<< orphan*/  callback; void* user_data; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  timeout; int /*<<< orphan*/  type; int /*<<< orphan*/  endpoint; int /*<<< orphan*/ * dev_handle; } ;
typedef  int /*<<< orphan*/  libusb_transfer_cb_fn ;
typedef  int /*<<< orphan*/  libusb_device_handle ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUSB_TRANSFER_TYPE_BULK ; 

void
libusb_fill_bulk_transfer(struct libusb_transfer *transfer, 
    libusb_device_handle *devh, uint8_t endpoint, uint8_t *buf, 
    int length, libusb_transfer_cb_fn callback, void *user_data,
    uint32_t timeout)
{
	transfer->dev_handle = devh;
	transfer->endpoint = endpoint;
	transfer->type = LIBUSB_TRANSFER_TYPE_BULK;
	transfer->timeout = timeout;
	transfer->buffer = buf;
	transfer->length = length;
	transfer->user_data = user_data;
	transfer->callback = callback;
}