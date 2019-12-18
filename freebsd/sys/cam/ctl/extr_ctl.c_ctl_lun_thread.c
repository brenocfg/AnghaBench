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
struct ctl_softc {int /*<<< orphan*/ * lun_thread; int /*<<< orphan*/  ctl_lock; int /*<<< orphan*/  pending_lun_queue; int /*<<< orphan*/  shutdown; } ;
struct ctl_be_lun {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  PDROP ; 
 scalar_t__ PUSER ; 
 struct ctl_be_lun* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_create_lun (struct ctl_be_lun*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_lun_thread(void *arg)
{
	struct ctl_softc *softc = (struct ctl_softc *)arg;
	struct ctl_be_lun *be_lun;

	CTL_DEBUG_PRINT(("ctl_lun_thread starting\n"));
	thread_lock(curthread);
	sched_prio(curthread, PUSER - 1);
	thread_unlock(curthread);

	while (!softc->shutdown) {
		mtx_lock(&softc->ctl_lock);
		be_lun = STAILQ_FIRST(&softc->pending_lun_queue);
		if (be_lun != NULL) {
			STAILQ_REMOVE_HEAD(&softc->pending_lun_queue, links);
			mtx_unlock(&softc->ctl_lock);
			ctl_create_lun(be_lun);
			continue;
		}

		/* Sleep until we have something to do. */
		mtx_sleep(&softc->pending_lun_queue, &softc->ctl_lock,
		    PDROP, "-", 0);
	}
	softc->lun_thread = NULL;
	kthread_exit();
}