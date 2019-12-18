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
struct usb_process {scalar_t__ up_curtd; int up_dsleep; int /*<<< orphan*/  up_mtx; int /*<<< orphan*/  up_drain; scalar_t__ up_gone; int /*<<< orphan*/  up_qhead; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tqe_prev; } ;
struct usb_proc_msg {TYPE_1__ pm_qentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct usb_proc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qentry ; 

void
usb_proc_mwait(struct usb_process *up, void *_pm0, void *_pm1)
{
	struct usb_proc_msg *pm0 = _pm0;
	struct usb_proc_msg *pm1 = _pm1;

	/* check if gone */
	if (up->up_gone)
		return;

	USB_MTX_ASSERT(up->up_mtx, MA_OWNED);

	if (up->up_curtd == curthread) {
		/* Just remove the messages from the queue. */
		if (pm0->pm_qentry.tqe_prev) {
			TAILQ_REMOVE(&up->up_qhead, pm0, pm_qentry);
			pm0->pm_qentry.tqe_prev = NULL;
		}
		if (pm1->pm_qentry.tqe_prev) {
			TAILQ_REMOVE(&up->up_qhead, pm1, pm_qentry);
			pm1->pm_qentry.tqe_prev = NULL;
		}
	} else
		while (pm0->pm_qentry.tqe_prev ||
		    pm1->pm_qentry.tqe_prev) {
			/* check if config thread is gone */
			if (up->up_gone)
				break;
			up->up_dsleep = 1;
			cv_wait(&up->up_drain, up->up_mtx);
		}
}