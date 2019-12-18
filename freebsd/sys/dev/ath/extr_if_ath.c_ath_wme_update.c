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
struct ieee80211com {struct ath_softc* ic_softc; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WME_AC_BE ; 
 int /*<<< orphan*/  WME_AC_BK ; 
 int /*<<< orphan*/  WME_AC_VI ; 
 int /*<<< orphan*/  WME_AC_VO ; 
 int /*<<< orphan*/  ath_txq_update (struct ath_softc*,int /*<<< orphan*/ ) ; 

int
ath_wme_update(struct ieee80211com *ic)
{
	struct ath_softc *sc = ic->ic_softc;

	return !ath_txq_update(sc, WME_AC_BE) ||
	    !ath_txq_update(sc, WME_AC_BK) ||
	    !ath_txq_update(sc, WME_AC_VI) ||
	    !ath_txq_update(sc, WME_AC_VO) ? EIO : 0;
}