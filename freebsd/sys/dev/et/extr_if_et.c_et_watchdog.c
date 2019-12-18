#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * txsd_status; int /*<<< orphan*/  txsd_dmap; int /*<<< orphan*/  txsd_dtag; } ;
struct et_softc {scalar_t__ watchdog_timer; TYPE_2__* ifp; TYPE_1__ sc_tx_status; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  ET_LOCK_ASSERT (struct et_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et_init_locked (struct et_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
et_watchdog(struct et_softc *sc)
{
	uint32_t status;

	ET_LOCK_ASSERT(sc);

	if (sc->watchdog_timer == 0 || --sc->watchdog_timer)
		return (0);

	bus_dmamap_sync(sc->sc_tx_status.txsd_dtag, sc->sc_tx_status.txsd_dmap,
	    BUS_DMASYNC_POSTREAD);
	status = le32toh(*(sc->sc_tx_status.txsd_status));
	if_printf(sc->ifp, "watchdog timed out (0x%08x) -- resetting\n",
	    status);

	if_inc_counter(sc->ifp, IFCOUNTER_OERRORS, 1);
	sc->ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	et_init_locked(sc);
	return (EJUSTRETURN);
}