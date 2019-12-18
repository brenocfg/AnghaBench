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
struct usb_xfer {int max_frame_size; int max_packet_size; int max_packet_count; } ;

/* Variables and functions */

__attribute__((used)) static void
usbd_update_max_frame_size(struct usb_xfer *xfer)
{
	/* compute maximum frame size */
	/* this computation should not overflow 16-bit */
	/* max = 15 * 1024 */

	xfer->max_frame_size = xfer->max_packet_size * xfer->max_packet_count;
}