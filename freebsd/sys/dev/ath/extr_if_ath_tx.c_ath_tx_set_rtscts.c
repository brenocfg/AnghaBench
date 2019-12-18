#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ath_softc {size_t sc_protrix; int /*<<< orphan*/  sc_mrrprot; int /*<<< orphan*/  sc_ah; TYPE_4__* sc_currates; } ;
struct TYPE_9__ {int bfs_txflags; size_t bfs_ctsrate; scalar_t__ bfs_ctsrate0; TYPE_2__* bfs_rc; int /*<<< orphan*/  bfs_try0; scalar_t__ bfs_ismrr; int /*<<< orphan*/  bfs_ctsduration; int /*<<< orphan*/  bfs_pktlen; int /*<<< orphan*/  bfs_shpream; scalar_t__ bfs_doprot; } ;
struct ath_buf {TYPE_3__ bf_state; } ;
struct TYPE_10__ {TYPE_1__* info; } ;
struct TYPE_8__ {size_t rix; int /*<<< orphan*/  tries; } ;
struct TYPE_7__ {size_t controlRate; } ;
typedef  TYPE_4__ HAL_RATE_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TXMGTTRY ; 
 int HAL_TXDESC_CTSENA ; 
 int HAL_TXDESC_RTSENA ; 
 int /*<<< orphan*/  ath_tx_calc_ctsduration (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__ const*,int) ; 
 size_t ath_tx_findrix (struct ath_softc*,scalar_t__) ; 
 size_t ath_tx_get_rtscts_rate (int /*<<< orphan*/ ,TYPE_4__ const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_tx_is_11n (struct ath_softc*) ; 

__attribute__((used)) static void
ath_tx_set_rtscts(struct ath_softc *sc, struct ath_buf *bf)
{
	uint16_t ctsduration = 0;
	uint8_t ctsrate = 0;
	uint8_t rix = bf->bf_state.bfs_rc[0].rix;
	uint8_t cix = 0;
	const HAL_RATE_TABLE *rt = sc->sc_currates;

	/*
	 * No RTS/CTS enabled? Don't bother.
	 */
	if ((bf->bf_state.bfs_txflags &
	    (HAL_TXDESC_RTSENA | HAL_TXDESC_CTSENA)) == 0) {
		/* XXX is this really needed? */
		bf->bf_state.bfs_ctsrate = 0;
		bf->bf_state.bfs_ctsduration = 0;
		return;
	}

	/*
	 * If protection is enabled, use the protection rix control
	 * rate. Otherwise use the rate0 control rate.
	 */
	if (bf->bf_state.bfs_doprot)
		rix = sc->sc_protrix;
	else
		rix = bf->bf_state.bfs_rc[0].rix;

	/*
	 * If the raw path has hard-coded ctsrate0 to something,
	 * use it.
	 */
	if (bf->bf_state.bfs_ctsrate0 != 0)
		cix = ath_tx_findrix(sc, bf->bf_state.bfs_ctsrate0);
	else
		/* Control rate from above */
		cix = rt->info[rix].controlRate;

	/* Calculate the rtscts rate for the given cix */
	ctsrate = ath_tx_get_rtscts_rate(sc->sc_ah, rt, cix,
	    bf->bf_state.bfs_shpream);

	/* The 11n chipsets do ctsduration calculations for you */
	if (! ath_tx_is_11n(sc))
		ctsduration = ath_tx_calc_ctsduration(sc->sc_ah, rix, cix,
		    bf->bf_state.bfs_shpream, bf->bf_state.bfs_pktlen,
		    rt, bf->bf_state.bfs_txflags);

	/* Squirrel away in ath_buf */
	bf->bf_state.bfs_ctsrate = ctsrate;
	bf->bf_state.bfs_ctsduration = ctsduration;
	
	/*
	 * Must disable multi-rate retry when using RTS/CTS.
	 */
	if (!sc->sc_mrrprot) {
		bf->bf_state.bfs_ismrr = 0;
		bf->bf_state.bfs_try0 =
		    bf->bf_state.bfs_rc[0].tries = ATH_TXMGTTRY; /* XXX ew */
	}
}