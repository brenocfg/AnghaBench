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
struct usb_process {int up_msleep; int /*<<< orphan*/  up_mtx; int /*<<< orphan*/  up_cv; int /*<<< orphan*/ * up_ptr; int /*<<< orphan*/  up_drain; scalar_t__ up_dsleep; int /*<<< orphan*/  up_qhead; scalar_t__ up_gone; struct thread* up_curtd; int /*<<< orphan*/  up_prio; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tqe_prev; } ;
struct usb_proc_msg {TYPE_1__ pm_qentry; int /*<<< orphan*/  (* pm_callback ) (struct usb_proc_msg*) ;} ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct usb_proc_msg*,...) ; 
 struct usb_proc_msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct usb_proc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_THREAD_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_THREAD_SUSPEND_CHECK () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qentry ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_proc_msg*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 scalar_t__ usb_pcount ; 
 int /*<<< orphan*/ * usbproc ; 

__attribute__((used)) static void
usb_process(void *arg)
{
	struct usb_process *up = arg;
	struct usb_proc_msg *pm;
	struct thread *td;

	/* in case of attach error, check for suspended */
	USB_THREAD_SUSPEND_CHECK();

	/* adjust priority */
	td = curthread;
	thread_lock(td);
	sched_prio(td, up->up_prio);
	thread_unlock(td);

	USB_MTX_LOCK(up->up_mtx);

	up->up_curtd = td;

	while (1) {

		if (up->up_gone)
			break;

		/*
		 * NOTE to reimplementors: dequeueing a command from the
		 * "used" queue and executing it must be atomic, with regard
		 * to the "up_mtx" mutex. That means any attempt to queue a
		 * command by another thread must be blocked until either:
		 *
		 * 1) the command sleeps
		 *
		 * 2) the command returns
		 *
		 * Here is a practical example that shows how this helps
		 * solving a problem:
		 *
		 * Assume that you want to set the baud rate on a USB serial
		 * device. During the programming of the device you don't
		 * want to receive nor transmit any data, because it will be
		 * garbage most likely anyway. The programming of our USB
		 * device takes 20 milliseconds and it needs to call
		 * functions that sleep.
		 *
		 * Non-working solution: Before we queue the programming
		 * command, we stop transmission and reception of data. Then
		 * we queue a programming command. At the end of the
		 * programming command we enable transmission and reception
		 * of data.
		 *
		 * Problem: If a second programming command is queued while the
		 * first one is sleeping, we end up enabling transmission
		 * and reception of data too early.
		 *
		 * Working solution: Before we queue the programming command,
		 * we stop transmission and reception of data. Then we queue
		 * a programming command. Then we queue a second command
		 * that only enables transmission and reception of data.
		 *
		 * Why it works: If a second programming command is queued
		 * while the first one is sleeping, then the queueing of a
		 * second command to enable the data transfers, will cause
		 * the previous one, which is still on the queue, to be
		 * removed from the queue, and re-inserted after the last
		 * baud rate programming command, which then gives the
		 * desired result.
		 */
		pm = TAILQ_FIRST(&up->up_qhead);

		if (pm) {
			DPRINTF("Message pm=%p, cb=%p (enter)\n",
			    pm, pm->pm_callback);

			(pm->pm_callback) (pm);

			if (pm == TAILQ_FIRST(&up->up_qhead)) {
				/* nothing changed */
				TAILQ_REMOVE(&up->up_qhead, pm, pm_qentry);
				pm->pm_qentry.tqe_prev = NULL;
			}
			DPRINTF("Message pm=%p (leave)\n", pm);

			continue;
		}
		/* end of messages - check if anyone is waiting for sync */
		if (up->up_dsleep) {
			up->up_dsleep = 0;
			cv_broadcast(&up->up_drain);
		}
		up->up_msleep = 1;
		cv_wait(&up->up_cv, up->up_mtx);
	}

	up->up_ptr = NULL;
	cv_signal(&up->up_cv);
	USB_MTX_UNLOCK(up->up_mtx);
#if (__FreeBSD_version >= 800000)
	/* Clear the proc pointer if this is the last thread. */
	if (--usb_pcount == 0)
		usbproc = NULL;
#endif

	USB_THREAD_EXIT(0);
}