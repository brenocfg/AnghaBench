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
struct rtwn_softc {struct r12a_softc* sc_priv; } ;
struct r12a_softc {int ampdu_max_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_AMPDU_MAX_LENGTH ; 
 int R12A_AMPDU_MAX_TIME ; 
 int /*<<< orphan*/  R12A_HT_SINGLE_AMPDU ; 
 int R12A_HT_SINGLE_AMPDU_PKT_ENA ; 
 int R92C_MAX_AGGR_NUM ; 
 int R92C_PIFS ; 
 int /*<<< orphan*/  R92C_RSV_CTRL ; 
 int R92C_RXDMA_STATUS ; 
 int R92C_RX_PKT_LIMIT ; 
 int R92C_USTIME_EDCA ; 
 int R92C_USTIME_TSF ; 
 int /*<<< orphan*/  r12au_arfb_init (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_r12a_init_ampdu_fwhw (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_r12a_init_burstlen (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int,int) ; 
 int /*<<< orphan*/  rtwn_write_2 (struct rtwn_softc*,int,int) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r12au_init_ampdu(struct rtwn_softc *sc)
{
	struct r12a_softc *rs = sc->sc_priv;

	/* Rx interval (USB3). */
	rtwn_write_1(sc, 0xf050, 0x01);

	/* burst length = 4 */
	rtwn_write_2(sc, R92C_RXDMA_STATUS, 0x7400);

	rtwn_write_1(sc, R92C_RXDMA_STATUS + 1, 0xf5);

	/* Setup AMPDU aggregation. */
	rtwn_write_1(sc, R12A_AMPDU_MAX_TIME, rs->ampdu_max_time);
	rtwn_write_4(sc, R12A_AMPDU_MAX_LENGTH, 0xffffffff);

	/* 80 MHz clock (again?) */
	rtwn_write_1(sc, R92C_USTIME_TSF, 0x50);
	rtwn_write_1(sc, R92C_USTIME_EDCA, 0x50);

	rtwn_r12a_init_burstlen(sc);

	/* Enable single packet AMPDU. */
	rtwn_setbits_1(sc, R12A_HT_SINGLE_AMPDU, 0,
	    R12A_HT_SINGLE_AMPDU_PKT_ENA);

	/* 11K packet length for VHT. */
	rtwn_write_1(sc, R92C_RX_PKT_LIMIT, 0x18);

	rtwn_write_1(sc, R92C_PIFS, 0);

	rtwn_write_2(sc, R92C_MAX_AGGR_NUM, 0x1f1f);

	rtwn_r12a_init_ampdu_fwhw(sc);

	/* Do not reset MAC. */
	rtwn_setbits_1(sc, R92C_RSV_CTRL, 0, 0x60);

	r12au_arfb_init(sc);
}