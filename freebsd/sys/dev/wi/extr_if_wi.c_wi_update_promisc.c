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
struct wi_softc {int dummy; } ;
struct ieee80211com {scalar_t__ ic_opmode; scalar_t__ ic_promisc; struct wi_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  WI_LOCK (struct wi_softc*) ; 
 int /*<<< orphan*/  WI_RID_PROMISC ; 
 int /*<<< orphan*/  WI_UNLOCK (struct wi_softc*) ; 
 int /*<<< orphan*/  wi_write_val (struct wi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wi_update_promisc(struct ieee80211com *ic)
{
	struct wi_softc *sc = ic->ic_softc;

	WI_LOCK(sc);
	/* XXX handle WEP special case handling? */
	wi_write_val(sc, WI_RID_PROMISC, 
	    (ic->ic_opmode == IEEE80211_M_MONITOR ||
	     (ic->ic_promisc > 0)));
	WI_UNLOCK(sc);
}