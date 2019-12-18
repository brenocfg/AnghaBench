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
typedef  size_t usb_frcount_t ;
struct usb_xfer {size_t max_frame_count; int /*<<< orphan*/ * frlengths; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

usb_frlength_t
usbd_xfer_frame_len(struct usb_xfer *xfer, usb_frcount_t frindex)
{
	KASSERT(frindex < xfer->max_frame_count, ("frame index overflow"));

	return (xfer->frlengths[frindex]);
}