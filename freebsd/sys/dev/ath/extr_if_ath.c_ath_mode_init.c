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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ieee80211com {int /*<<< orphan*/  ic_macaddr; } ;
struct ath_softc {struct ath_hal* sc_ah; struct ieee80211com sc_ic; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_calcrxfilter (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hal_setmac (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_setopmode (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_setrxfilter (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_update_mcast_hw (struct ath_softc*) ; 

void
ath_mode_init(struct ath_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ath_hal *ah = sc->sc_ah;
	u_int32_t rfilt;

	/* XXX power state? */

	/* configure rx filter */
	rfilt = ath_calcrxfilter(sc);
	ath_hal_setrxfilter(ah, rfilt);

	/* configure operational mode */
	ath_hal_setopmode(ah);

	/* handle any link-level address change */
	ath_hal_setmac(ah, ic->ic_macaddr);

	/* calculate and install multicast filter */
	ath_update_mcast_hw(sc);
}