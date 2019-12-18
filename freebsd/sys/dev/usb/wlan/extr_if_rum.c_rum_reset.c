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
typedef  int u_long ;
struct rum_softc {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_state; int /*<<< orphan*/  iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct rum_softc* ic_softc; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_intval; } ;

/* Variables and functions */
 int ENETRESET ; 
#define  IEEE80211_IOC_POWERSAVE 131 
#define  IEEE80211_IOC_POWERSAVESLEEP 130 
#define  IEEE80211_IOC_PROTMODE 129 
#define  IEEE80211_IOC_RTSTHRESHOLD 128 
 int /*<<< orphan*/  IEEE80211_S_SLEEP ; 
 int /*<<< orphan*/  RT2573_AUTO_WAKEUP ; 
 int /*<<< orphan*/  RT2573_MAC_CSR11 ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_ref_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_clrbits (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rum_set_sleep_time (struct rum_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_setbits (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rum_reset(struct ieee80211vap *vap, u_long cmd)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_node *ni;
	struct rum_softc *sc = ic->ic_softc;
	int error;

	switch (cmd) {
	case IEEE80211_IOC_POWERSAVE:
	case IEEE80211_IOC_PROTMODE:
	case IEEE80211_IOC_RTSTHRESHOLD:
		error = 0;
		break;
	case IEEE80211_IOC_POWERSAVESLEEP:
		ni = ieee80211_ref_node(vap->iv_bss);

		RUM_LOCK(sc);
		error = rum_set_sleep_time(sc, ni->ni_intval);
		if (vap->iv_state == IEEE80211_S_SLEEP) {
			/* Use new values for wakeup timer. */
			rum_clrbits(sc, RT2573_MAC_CSR11, RT2573_AUTO_WAKEUP);
			rum_setbits(sc, RT2573_MAC_CSR11, RT2573_AUTO_WAKEUP);
		}
		/* XXX send reassoc */
		RUM_UNLOCK(sc);

		ieee80211_free_node(ni);
		break;
	default:
		error = ENETRESET;
		break;
	}

	return (error);
}