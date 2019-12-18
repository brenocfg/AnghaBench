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
struct libusb20_transfer {int /*<<< orphan*/  flags; } ;

/* Variables and functions */

void
libusb20_tr_set_flags(struct libusb20_transfer *xfer, uint8_t flags)
{
	xfer->flags = flags;
	return;
}