#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * proc_task; } ;
struct TYPE_4__ {int /*<<< orphan*/ * proc_task; } ;
struct TYPE_6__ {int /*<<< orphan*/  hv_appvss_dev; int /*<<< orphan*/  hv_vss_dev; TYPE_2__ app_sc; TYPE_1__ daemon_sc; int /*<<< orphan*/  pending_mutex; } ;
typedef  TYPE_3__ hv_vss_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_vss_destroy_send_receive_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int vmbus_ic_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hv_vss_detach(device_t dev)
{
	hv_vss_sc *sc = (hv_vss_sc*)device_get_softc(dev);
	mtx_destroy(&sc->pending_mutex);
	if (sc->daemon_sc.proc_task != NULL) {
		PROC_LOCK(sc->daemon_sc.proc_task);
		kern_psignal(sc->daemon_sc.proc_task, SIGKILL);
		PROC_UNLOCK(sc->daemon_sc.proc_task);
	}
	if (sc->app_sc.proc_task != NULL) {
		PROC_LOCK(sc->app_sc.proc_task);
		kern_psignal(sc->app_sc.proc_task, SIGKILL);
		PROC_UNLOCK(sc->app_sc.proc_task);
	}
	hv_vss_destroy_send_receive_queue(dev);
	destroy_dev(sc->hv_vss_dev);
	destroy_dev(sc->hv_appvss_dev);
	return (vmbus_ic_detach(dev));
}