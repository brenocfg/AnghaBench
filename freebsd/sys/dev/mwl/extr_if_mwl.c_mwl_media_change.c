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
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ieee80211vap {int dummy; } ;

/* Variables and functions */
 int ENETRESET ; 
 int ieee80211_media_change (struct ifnet*) ; 
 int /*<<< orphan*/  mwl_setrates (struct ieee80211vap*) ; 

__attribute__((used)) static int
mwl_media_change(struct ifnet *ifp)
{
	struct ieee80211vap *vap = ifp->if_softc;
	int error;

	error = ieee80211_media_change(ifp);
	/* NB: only the fixed rate can change and that doesn't need a reset */
	if (error == ENETRESET) {
		mwl_setrates(vap);
		error = 0;
	}
	return error;
}