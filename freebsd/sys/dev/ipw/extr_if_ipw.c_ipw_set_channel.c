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
struct ipw_softc {int dummy; } ;
struct ieee80211com {scalar_t__ ic_opmode; int /*<<< orphan*/  ic_curchan; struct ipw_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  IPW_LOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  IPW_UNLOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_disable (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_enable (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_setchannel (struct ipw_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipw_set_channel(struct ieee80211com *ic)
{
	struct ipw_softc *sc = ic->ic_softc;

	IPW_LOCK(sc);
	if (ic->ic_opmode == IEEE80211_M_MONITOR) {
		ipw_disable(sc);
		ipw_setchannel(sc, ic->ic_curchan);
		ipw_enable(sc);
	}
	IPW_UNLOCK(sc);
}