#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t usb_frcount_t ;
struct usb_xfer {size_t max_frame_count; int* frlengths; TYPE_1__* frbuffers; } ;
struct TYPE_2__ {void* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

void
usbd_xfer_frame_data(struct usb_xfer *xfer, usb_frcount_t frindex,
    void **ptr, int *len)
{
	KASSERT(frindex < xfer->max_frame_count, ("frame index overflow"));

	if (ptr != NULL)
		*ptr = xfer->frbuffers[frindex].buffer;
	if (len != NULL)
		*len = xfer->frlengths[frindex];
}