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
struct ctl_thread {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/ * thread; } ;
struct ctl_softc {scalar_t__ is_single; int shutdown; int /*<<< orphan*/  sysctl_ctx; struct ctl_softc* ctl_ports; struct ctl_softc* ctl_port_mask; struct ctl_softc* ctl_lun_mask; struct ctl_softc* ctl_luns; int /*<<< orphan*/  ctl_lock; int /*<<< orphan*/  io_zone; struct ctl_thread* thresh_thread; int /*<<< orphan*/ * lun_thread; struct ctl_thread pending_lun_queue; struct ctl_thread* threads; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct ctl_softc* control_softc ; 
 int /*<<< orphan*/  ctl_frontend_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_tpc_shutdown (struct ctl_softc*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ha_frontend ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct ctl_thread*) ; 
 int worker_threads ; 

__attribute__((used)) static int
ctl_shutdown(void)
{
	struct ctl_softc *softc = control_softc;
	int i;

	if (softc->is_single == 0)
		ctl_frontend_deregister(&ha_frontend);

	destroy_dev(softc->dev);

	/* Shutdown CTL threads. */
	softc->shutdown = 1;
	for (i = 0; i < worker_threads; i++) {
		struct ctl_thread *thr = &softc->threads[i];
		while (thr->thread != NULL) {
			wakeup(thr);
			if (thr->thread != NULL)
				pause("CTL thr shutdown", 1);
		}
		mtx_destroy(&thr->queue_lock);
	}
	while (softc->lun_thread != NULL) {
		wakeup(&softc->pending_lun_queue);
		if (softc->lun_thread != NULL)
			pause("CTL thr shutdown", 1);
	}
	while (softc->thresh_thread != NULL) {
		wakeup(softc->thresh_thread);
		if (softc->thresh_thread != NULL)
			pause("CTL thr shutdown", 1);
	}

	ctl_tpc_shutdown(softc);
	uma_zdestroy(softc->io_zone);
	mtx_destroy(&softc->ctl_lock);

	free(softc->ctl_luns, M_DEVBUF);
	free(softc->ctl_lun_mask, M_DEVBUF);
	free(softc->ctl_port_mask, M_DEVBUF);
	free(softc->ctl_ports, M_DEVBUF);

	sysctl_ctx_free(&softc->sysctl_ctx);

	free(softc, M_DEVBUF);
	control_softc = NULL;
	return (0);
}