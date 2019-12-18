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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ R92C_RXDMA_AGG_PG_TH ; 
 int /*<<< orphan*/  R92C_TRXDMA_CTRL ; 
 int /*<<< orphan*/  R92C_TRXDMA_CTRL_RXDMA_AGG_EN ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,scalar_t__,int) ; 

void
r88eu_init_rx_agg(struct rtwn_softc *sc)
{
	/* XXX merge? */
	rtwn_setbits_1(sc, R92C_TRXDMA_CTRL, 0,
	    R92C_TRXDMA_CTRL_RXDMA_AGG_EN);
	/* XXX dehardcode */
	rtwn_write_1(sc, R92C_RXDMA_AGG_PG_TH, 48);
	rtwn_write_1(sc, R92C_RXDMA_AGG_PG_TH + 1, 4);
}