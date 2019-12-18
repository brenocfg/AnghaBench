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
struct usb_process {int /*<<< orphan*/  up_qhead; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tqe_prev; } ;
struct usb_proc_msg {TYPE_1__ pm_qentry; int /*<<< orphan*/  (* pm_callback ) (struct usb_proc_msg*) ;} ;

/* Variables and functions */
 struct usb_proc_msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct usb_proc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qentry ; 
 int /*<<< orphan*/  stub1 (struct usb_proc_msg*) ; 
 int /*<<< orphan*/  usb_proc_mtx ; 

__attribute__((used)) static int
usb_do_process(struct usb_process *up)
{
	struct usb_proc_msg *pm;
	int worked = 0;

	mtx_lock(&usb_proc_mtx);

repeat:
	pm = TAILQ_FIRST(&up->up_qhead);

	if (pm != NULL) {

		worked = 1;

		(pm->pm_callback) (pm);

		if (pm == TAILQ_FIRST(&up->up_qhead)) {
			/* nothing changed */
			TAILQ_REMOVE(&up->up_qhead, pm, pm_qentry);
			pm->pm_qentry.tqe_prev = NULL;
		}
		goto repeat;
	}
	mtx_unlock(&usb_proc_mtx);

	return (worked);
}