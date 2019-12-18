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
struct libusb_transfer {int* user_data; int /*<<< orphan*/  dev_handle; } ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_TRANSFER ; 
 int /*<<< orphan*/ * libusb10_get_context_by_device_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
libusb10_do_transfer_cb(struct libusb_transfer *transfer)
{
	libusb_context *ctx;
	int *pdone;

	ctx = libusb10_get_context_by_device_handle(transfer->dev_handle);

	DPRINTF(ctx, LIBUSB_DEBUG_TRANSFER, "sync I/O done");

	pdone = transfer->user_data;
	*pdone = 1;
}