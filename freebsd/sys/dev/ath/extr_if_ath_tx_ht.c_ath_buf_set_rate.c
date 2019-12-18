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
struct ieee80211_node {int dummy; } ;
struct ath_softc {int sc_debug; struct ath_hal* sc_ah; } ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct TYPE_2__ {scalar_t__ bfs_atype; int bfs_ctsrate; int bfs_txflags; } ;
struct ath_buf {TYPE_1__ bf_state; struct ath_desc* bf_desc; } ;
typedef  int /*<<< orphan*/  series ;
typedef  int /*<<< orphan*/  HAL_11N_RATE_SERIES ;

/* Variables and functions */
 int ATH_DEBUG_XMIT ; 
 scalar_t__ HAL_PKT_TYPE_PSPOLL ; 
 int /*<<< orphan*/  ath_hal_set11nratescenario (struct ath_hal*,struct ath_desc*,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ath_rateseries_print (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_rateseries_setup (struct ath_softc*,struct ieee80211_node*,struct ath_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

void
ath_buf_set_rate(struct ath_softc *sc, struct ieee80211_node *ni,
    struct ath_buf *bf)
{
	HAL_11N_RATE_SERIES series[4];
	struct ath_desc *ds = bf->bf_desc;
	struct ath_hal *ah = sc->sc_ah;
	int is_pspoll = (bf->bf_state.bfs_atype == HAL_PKT_TYPE_PSPOLL);
	int ctsrate = bf->bf_state.bfs_ctsrate;
	int flags = bf->bf_state.bfs_txflags;

	/* Setup rate scenario */
	memset(&series, 0, sizeof(series));

	ath_rateseries_setup(sc, ni, bf, series);

#ifdef	ATH_DEBUG
	if (sc->sc_debug & ATH_DEBUG_XMIT)
		ath_rateseries_print(sc, series);
#endif

	/* Set rate scenario */
	/*
	 * Note: Don't allow hardware to override the duration on
	 * ps-poll packets.
	 */
	ath_hal_set11nratescenario(ah, ds,
	    !is_pspoll,	/* whether to override the duration or not */
	    ctsrate,	/* rts/cts rate */
	    series,	/* 11n rate series */
	    4,		/* number of series */
	    flags);

	/* Set burst duration */
	/*
	 * This is only required when doing 11n burst, not aggregation
	 * ie, if there's a second frame in a RIFS or A-MPDU burst
	 * w/ >1 A-MPDU frame bursting back to back.
	 * Normal A-MPDU doesn't do bursting -between- aggregates.
	 *
	 * .. and it's highly likely this won't ever be implemented
	 */
	//ath_hal_set11nburstduration(ah, ds, 8192);
}