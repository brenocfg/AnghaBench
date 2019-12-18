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
typedef  int /*<<< orphan*/  uint32_t ;
struct libusb20_transfer {int /*<<< orphan*/  maxFrames; } ;

/* Variables and functions */

uint32_t
libusb20_tr_get_max_frames(struct libusb20_transfer *xfer)
{
	return (xfer->maxFrames);
}