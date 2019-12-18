#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  link_up; } ;
struct bxe_softc {struct bxe_fastpath* fp; TYPE_1__ link_vars; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_queue_full_return; } ;
struct bxe_fastpath {TYPE_2__ eth_q_stats; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_FP_TX_LOCK (struct bxe_fastpath*) ; 
 int /*<<< orphan*/  BXE_FP_TX_UNLOCK (struct bxe_fastpath*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bxe_tx_start_locked (struct bxe_softc*,int /*<<< orphan*/ ,struct bxe_fastpath*) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 struct bxe_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_tx_start(if_t ifp)
{
    struct bxe_softc *sc;
    struct bxe_fastpath *fp;

    sc = if_getsoftc(ifp);

    if (!(if_getdrvflags(ifp) & IFF_DRV_RUNNING)) {
        BLOGW(sc, "Interface not running, ignoring transmit request\n");
        return;
    }

    if (!sc->link_vars.link_up) {
        BLOGW(sc, "Interface link is down, ignoring transmit request\n");
        return;
    }

    fp = &sc->fp[0];

    if (if_getdrvflags(ifp) & IFF_DRV_OACTIVE) {
        fp->eth_q_stats.tx_queue_full_return++;
        return;
    }

    BXE_FP_TX_LOCK(fp);
    bxe_tx_start_locked(sc, ifp, fp);
    BXE_FP_TX_UNLOCK(fp);
}