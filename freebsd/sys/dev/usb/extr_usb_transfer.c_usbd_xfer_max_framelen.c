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
typedef  int /*<<< orphan*/  usb_frlength_t ;
struct usb_xfer {int /*<<< orphan*/  max_frame_size; } ;

/* Variables and functions */

usb_frlength_t
usbd_xfer_max_framelen(struct usb_xfer *xfer)
{
	return (xfer->max_frame_size);
}