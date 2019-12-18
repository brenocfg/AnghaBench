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
typedef  int /*<<< orphan*/  usb_frcount_t ;
struct usb_xfer {int /*<<< orphan*/  nframes; } ;

/* Variables and functions */

void
usbd_xfer_set_frames(struct usb_xfer *xfer, usb_frcount_t n)
{
	xfer->nframes = n;
}