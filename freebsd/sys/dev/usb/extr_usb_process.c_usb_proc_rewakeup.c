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
struct usb_process {scalar_t__ up_msleep; int /*<<< orphan*/  up_cv; int /*<<< orphan*/ * up_mtx; scalar_t__ up_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

void
usb_proc_rewakeup(struct usb_process *up)
{
	/* check if not initialised */
	if (up->up_mtx == NULL)
		return;
	/* check if gone */
	if (up->up_gone)
		return;

	USB_MTX_ASSERT(up->up_mtx, MA_OWNED);

	if (up->up_msleep == 0) {
		/* re-wakeup */
		cv_signal(&up->up_cv);
	}
}