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
struct libusb_transfer {int dummy; } ;
struct libusb_super_transfer {int /*<<< orphan*/  stream_id; } ;

/* Variables and functions */

uint32_t
libusb_transfer_get_stream_id(struct libusb_transfer *transfer)
{
	struct libusb_super_transfer *sxfer;

	if (transfer == NULL)
		return (0);

	sxfer = (struct libusb_super_transfer *)(
	    ((uint8_t *)transfer) - sizeof(*sxfer));

	/* get stream ID */
	return (sxfer->stream_id);
}