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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct bxe_softc {int /*<<< orphan*/  ifp; } ;
struct bxe_fastpath {scalar_t__ tx_bd_cons; scalar_t__ tx_pkt_cons; scalar_t__ tx_pkt_prod; scalar_t__ watchdog_timer; int /*<<< orphan*/  index; int /*<<< orphan*/ * tx_cons_sb; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BXE_FP_TX_LOCK_ASSERT (struct bxe_fastpath*) ; 
 scalar_t__ BXE_TX_CLEANUP_THRESHOLD ; 
 scalar_t__ BXE_TX_TIMEOUT ; 
 int /*<<< orphan*/  DBG_TX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TX_BD (scalar_t__) ; 
 scalar_t__ bxe_free_tx_pkt (struct bxe_softc*,struct bxe_fastpath*,scalar_t__) ; 
 scalar_t__ bxe_tx_avail (struct bxe_softc*,struct bxe_fastpath*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static uint8_t
bxe_txeof(struct bxe_softc    *sc,
          struct bxe_fastpath *fp)
{
    if_t ifp = sc->ifp;
    uint16_t bd_cons, hw_cons, sw_cons, pkt_cons;
    uint16_t tx_bd_avail;

    BXE_FP_TX_LOCK_ASSERT(fp);

    bd_cons = fp->tx_bd_cons;
    hw_cons = le16toh(*fp->tx_cons_sb);
    sw_cons = fp->tx_pkt_cons;

    while (sw_cons != hw_cons) {
        pkt_cons = TX_BD(sw_cons);

        BLOGD(sc, DBG_TX,
              "TX: fp[%d]: hw_cons=%u sw_cons=%u pkt_cons=%u\n",
              fp->index, hw_cons, sw_cons, pkt_cons);

        bd_cons = bxe_free_tx_pkt(sc, fp, pkt_cons);

        sw_cons++;
    }

    fp->tx_pkt_cons = sw_cons;
    fp->tx_bd_cons  = bd_cons;

    BLOGD(sc, DBG_TX,
          "TX done: fp[%d]: hw_cons=%u sw_cons=%u sw_prod=%u\n",
          fp->index, hw_cons, fp->tx_pkt_cons, fp->tx_pkt_prod);

    mb();

    tx_bd_avail = bxe_tx_avail(sc, fp);

    if (tx_bd_avail < BXE_TX_CLEANUP_THRESHOLD) {
        if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, 0);
    } else {
        if_setdrvflagbits(ifp, 0, IFF_DRV_OACTIVE);
    }

    if (fp->tx_pkt_prod != fp->tx_pkt_cons) {
        /* reset the watchdog timer if there are pending transmits */
        fp->watchdog_timer = BXE_TX_TIMEOUT;
        return (TRUE);
    } else {
        /* clear watchdog when there are no pending transmits */
        fp->watchdog_timer = 0;
        return (FALSE);
    }
}