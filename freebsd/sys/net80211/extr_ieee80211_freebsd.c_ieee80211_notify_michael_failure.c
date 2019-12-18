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
typedef  int /*<<< orphan*/  u_int ;
struct ifnet {int /*<<< orphan*/  if_vnet; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_rx_tkipmic; } ;
struct ieee80211vap {TYPE_1__ iv_stats; struct ifnet* iv_ifp; } ;
struct ieee80211_michael_event {int /*<<< orphan*/  iev_keyix; int /*<<< orphan*/  iev_cipher; int /*<<< orphan*/  iev_src; int /*<<< orphan*/  iev_dst; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;
typedef  int /*<<< orphan*/  iev ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_CIPHER_TKIP ; 
 int /*<<< orphan*/  IEEE80211_MSG_CRYPTO ; 
 int /*<<< orphan*/  IEEE80211_NOTE_MAC (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTM_IEEE80211_MICHAEL ; 
 int /*<<< orphan*/  rt_ieee80211msg (struct ifnet*,int /*<<< orphan*/ ,struct ieee80211_michael_event*,int) ; 

void
ieee80211_notify_michael_failure(struct ieee80211vap *vap,
	const struct ieee80211_frame *wh, u_int keyix)
{
	struct ifnet *ifp = vap->iv_ifp;

	IEEE80211_NOTE_MAC(vap, IEEE80211_MSG_CRYPTO, wh->i_addr2,
	    "michael MIC verification failed <keyix %u>", keyix);
	vap->iv_stats.is_rx_tkipmic++;

	if (ifp != NULL) {		/* NB: for cipher test modules */
		struct ieee80211_michael_event iev;

		IEEE80211_ADDR_COPY(iev.iev_dst, wh->i_addr1);
		IEEE80211_ADDR_COPY(iev.iev_src, wh->i_addr2);
		iev.iev_cipher = IEEE80211_CIPHER_TKIP;
		iev.iev_keyix = keyix;
		CURVNET_SET(ifp->if_vnet);
		rt_ieee80211msg(ifp, RTM_IEEE80211_MICHAEL, &iev, sizeof(iev));
		CURVNET_RESTORE();
	}
}