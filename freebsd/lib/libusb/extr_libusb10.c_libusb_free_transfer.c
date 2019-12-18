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
struct libusb_transfer {int flags; struct libusb_super_transfer* buffer; } ;
struct libusb_super_transfer {int dummy; } ;

/* Variables and functions */
 int LIBUSB_TRANSFER_FREE_BUFFER ; 
 int /*<<< orphan*/  free (struct libusb_super_transfer*) ; 

void
libusb_free_transfer(struct libusb_transfer *uxfer)
{
	struct libusb_super_transfer *sxfer;

	if (uxfer == NULL)
		return;			/* be NULL safe */

	/* check if we should free the transfer buffer */
	if (uxfer->flags & LIBUSB_TRANSFER_FREE_BUFFER)
		free(uxfer->buffer);

	sxfer = (struct libusb_super_transfer *)(
	    (uint8_t *)uxfer - sizeof(*sxfer));

	free(sxfer);
}