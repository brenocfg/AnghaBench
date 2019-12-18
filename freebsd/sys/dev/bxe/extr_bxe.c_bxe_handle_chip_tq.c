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
struct bxe_softc {int /*<<< orphan*/  ifp; int /*<<< orphan*/  chip_tq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BXE_CORE_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_CORE_UNLOCK (struct bxe_softc*) ; 
#define  CHIP_TQ_REINIT 128 
 int /*<<< orphan*/  DBG_LOAD ; 
 int IFF_DRV_RUNNING ; 
 long atomic_load_acq_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxe_init_locked (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_periodic_stop (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stop_locked (struct bxe_softc*) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_handle_chip_tq(void *context,
                   int  pending)
{
    struct bxe_softc *sc = (struct bxe_softc *)context;
    long work = atomic_load_acq_long(&sc->chip_tq_flags);

    switch (work)
    {

    case CHIP_TQ_REINIT:
        if (if_getdrvflags(sc->ifp) & IFF_DRV_RUNNING) {
            /* restart the interface */
            BLOGD(sc, DBG_LOAD, "Restarting the interface...\n");
            bxe_periodic_stop(sc);
            BXE_CORE_LOCK(sc);
            bxe_stop_locked(sc);
            bxe_init_locked(sc);
            BXE_CORE_UNLOCK(sc);
        }
        break;

    default:
        break;
    }
}