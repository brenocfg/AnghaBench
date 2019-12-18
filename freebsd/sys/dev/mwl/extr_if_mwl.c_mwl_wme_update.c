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
struct mwl_softc {int dummy; } ;
struct ieee80211com {struct mwl_softc* ic_softc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WME_AC_BE ; 
 int /*<<< orphan*/  WME_AC_BK ; 
 int /*<<< orphan*/  WME_AC_VI ; 
 int /*<<< orphan*/  WME_AC_VO ; 
 int /*<<< orphan*/  mwl_txq_update (struct mwl_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwl_wme_update(struct ieee80211com *ic)
{
	struct mwl_softc *sc = ic->ic_softc;

	return !mwl_txq_update(sc, WME_AC_BE) ||
	    !mwl_txq_update(sc, WME_AC_BK) ||
	    !mwl_txq_update(sc, WME_AC_VI) ||
	    !mwl_txq_update(sc, WME_AC_VO) ? EIO : 0;
}