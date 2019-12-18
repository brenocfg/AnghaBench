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
struct TYPE_2__ {int /*<<< orphan*/  hv_kvp_dev; int /*<<< orphan*/ * daemon_task; } ;
typedef  TYPE_1__ hv_kvp_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vmbus_ic_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hv_kvp_detach(device_t dev)
{
	hv_kvp_sc *sc = (hv_kvp_sc*)device_get_softc(dev);

	if (sc->daemon_task != NULL) {
		PROC_LOCK(sc->daemon_task);
		kern_psignal(sc->daemon_task, SIGKILL);
		PROC_UNLOCK(sc->daemon_task);
	}

	destroy_dev(sc->hv_kvp_dev);
	return (vmbus_ic_detach(dev));
}