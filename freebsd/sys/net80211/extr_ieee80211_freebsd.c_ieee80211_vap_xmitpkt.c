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
struct mbuf {int dummy; } ;
struct ifnet {int (* if_transmit ) (struct ifnet*,struct mbuf*) ;} ;
struct ieee80211vap {int /*<<< orphan*/  iv_ic; struct ifnet* iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TX_UNLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

int
ieee80211_vap_xmitpkt(struct ieee80211vap *vap, struct mbuf *m)
{
	struct ifnet *ifp = vap->iv_ifp;

	/*
	 * When transmitting via the VAP, we shouldn't hold
	 * any IC TX lock as the VAP TX path will acquire it.
	 */
	IEEE80211_TX_UNLOCK_ASSERT(vap->iv_ic);

	return (ifp->if_transmit(ifp, m));

}