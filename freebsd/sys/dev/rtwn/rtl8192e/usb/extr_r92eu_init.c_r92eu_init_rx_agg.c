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
struct rtwn_softc {struct r92e_softc* sc_priv; } ;
struct r92e_softc {int ac_usb_dma_size; int ac_usb_dma_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_RXDMA_PRO ; 
 int /*<<< orphan*/  R92C_RXDMA_AGG_PG_TH ; 
 int /*<<< orphan*/  R92C_TRXDMA_CTRL ; 
 int R92C_TRXDMA_CTRL_RXDMA_AGG_EN ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r92eu_init_rx_agg(struct rtwn_softc *sc)
{
	struct r92e_softc *rs = sc->sc_priv;

	/* Rx aggregation (USB). */
	rtwn_setbits_1(sc, R12A_RXDMA_PRO, 0x20, 0x1e);
	rtwn_write_4(sc, R92C_RXDMA_AGG_PG_TH,
	    rs->ac_usb_dma_size | (rs->ac_usb_dma_time << 8));
	rtwn_setbits_1(sc, R92C_TRXDMA_CTRL, 0,
	    R92C_TRXDMA_CTRL_RXDMA_AGG_EN);
}