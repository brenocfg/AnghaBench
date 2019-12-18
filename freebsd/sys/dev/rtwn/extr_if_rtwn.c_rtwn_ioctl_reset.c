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
typedef  int u_long ;
struct rtwn_vap {int /*<<< orphan*/  id; } ;
struct rtwn_softc {int sc_flags; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_opmode; TYPE_1__* iv_ic; } ;
struct TYPE_2__ {struct rtwn_softc* ic_softc; } ;

/* Variables and functions */
 int ENETRESET ; 
 int EOPNOTSUPP ; 
#define  IEEE80211_IOC_HTPROTMODE 134 
#define  IEEE80211_IOC_LDPC 133 
#define  IEEE80211_IOC_POWERSAVE 132 
#define  IEEE80211_IOC_POWERSAVESLEEP 131 
#define  IEEE80211_IOC_PROTMODE 130 
#define  IEEE80211_IOC_RTSTHRESHOLD 129 
#define  IEEE80211_IOC_SHORTGI 128 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int RTWN_RUNNING ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int rtwn_set_pwrmode (struct rtwn_softc*,struct ieee80211vap*,int) ; 

__attribute__((used)) static int
rtwn_ioctl_reset(struct ieee80211vap *vap, u_long cmd)
{
	int error;

	switch (cmd) {
#ifndef RTWN_WITHOUT_UCODE
	case IEEE80211_IOC_POWERSAVE:
	case IEEE80211_IOC_POWERSAVESLEEP:
	{
		struct rtwn_softc *sc = vap->iv_ic->ic_softc;
		struct rtwn_vap *uvp = RTWN_VAP(vap);

		if (vap->iv_opmode == IEEE80211_M_STA && uvp->id == 0) {
			RTWN_LOCK(sc);
			if (sc->sc_flags & RTWN_RUNNING)
				error = rtwn_set_pwrmode(sc, vap, 1);
			else
				error = 0;
			RTWN_UNLOCK(sc);
			if (error != 0)
				error = ENETRESET;
		} else
			error = EOPNOTSUPP;
		break;
	}
#endif
	case IEEE80211_IOC_SHORTGI:
	case IEEE80211_IOC_RTSTHRESHOLD:
	case IEEE80211_IOC_PROTMODE:
	case IEEE80211_IOC_HTPROTMODE:
	case IEEE80211_IOC_LDPC:
		error = 0;
		break;
	default:
		error = ENETRESET;
		break;
	}

	return (error);
}