#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  scalar_t__ u_long ;
struct TYPE_6__ {int watchdog_countdown; int dying; int /*<<< orphan*/  co_hdl; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  tq; int /*<<< orphan*/  dev; TYPE_1__* ifp; } ;
typedef  TYPE_2__ mxge_softc_t ;
struct TYPE_5__ {int if_drv_flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int IFF_DRV_RUNNING ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),TYPE_2__*) ; 
 int mxge_ticks ; 
 int mxge_watchdog (TYPE_2__*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mxge_tick(void *arg)
{
	mxge_softc_t *sc = arg;
	u_long pkts = 0;
	int err = 0;
	int running, ticks;
	uint16_t cmd;

	ticks = mxge_ticks;
	running = sc->ifp->if_drv_flags & IFF_DRV_RUNNING;
	if (running) {
		if (!sc->watchdog_countdown) {
			err = mxge_watchdog(sc);
			sc->watchdog_countdown = 4;
		}
		sc->watchdog_countdown--;
	}
	if (pkts == 0) {
		/* ensure NIC did not suffer h/w fault while idle */
		cmd = pci_read_config(sc->dev, PCIR_COMMAND, 2);		
		if ((cmd & PCIM_CMD_BUSMASTEREN) == 0) {
			sc->dying = 2;
			taskqueue_enqueue(sc->tq, &sc->watchdog_task);
			err = ENXIO;
		}
		/* look less often if NIC is idle */
		ticks *= 4;
	}

	if (err == 0)
		callout_reset(&sc->co_hdl, ticks, mxge_tick, sc);

}