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
typedef  size_t uint16_t ;
struct libusb20_transfer {int /*<<< orphan*/ * ppBuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  libusb20_pass_ptr (void*) ; 

void
libusb20_tr_set_buffer(struct libusb20_transfer *xfer, void *buffer, uint16_t frIndex)
{
	xfer->ppBuffer[frIndex] = libusb20_pass_ptr(buffer);
	return;
}