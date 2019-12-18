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
struct libusb_transfer {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int LIBUSB_CONTROL_SETUP_SIZE ; 

uint8_t *
libusb_control_transfer_get_data(struct libusb_transfer *transfer)
{
	if (transfer->buffer == NULL)
		return (NULL);

	return (transfer->buffer + LIBUSB_CONTROL_SETUP_SIZE);
}