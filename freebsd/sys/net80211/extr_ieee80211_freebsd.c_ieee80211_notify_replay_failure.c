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
typedef  scalar_t__ u_int64_t ;
struct ifnet {int /*<<< orphan*/  if_vnet; } ;
struct ieee80211vap {struct ifnet* iv_ifp; } ;
struct ieee80211_replay_event {scalar_t__ iev_keyix; scalar_t__ iev_rsc; scalar_t__ iev_keyrsc; int /*<<< orphan*/  iev_cipher; int /*<<< orphan*/  iev_src; int /*<<< orphan*/  iev_dst; } ;
struct ieee80211_key {scalar_t__ wk_keyix; scalar_t__ wk_rxkeyix; scalar_t__* wk_keyrsc; TYPE_1__* wk_cipher; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  iev ;
struct TYPE_2__ {int /*<<< orphan*/  ic_cipher; int /*<<< orphan*/  ic_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_KEYIX_NONE ; 
 int /*<<< orphan*/  IEEE80211_MSG_CRYPTO ; 
 int /*<<< orphan*/  IEEE80211_NOTE_MAC (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RTM_IEEE80211_REPLAY ; 
 int /*<<< orphan*/  rt_ieee80211msg (struct ifnet*,int /*<<< orphan*/ ,struct ieee80211_replay_event*,int) ; 

void
ieee80211_notify_replay_failure(struct ieee80211vap *vap,
	const struct ieee80211_frame *wh, const struct ieee80211_key *k,
	u_int64_t rsc, int tid)
{
	struct ifnet *ifp = vap->iv_ifp;

	IEEE80211_NOTE_MAC(vap, IEEE80211_MSG_CRYPTO, wh->i_addr2,
	    "%s replay detected tid %d <rsc %ju, csc %ju, keyix %u rxkeyix %u>",
	    k->wk_cipher->ic_name, tid, (intmax_t) rsc,
	    (intmax_t) k->wk_keyrsc[tid],
	    k->wk_keyix, k->wk_rxkeyix);

	if (ifp != NULL) {		/* NB: for cipher test modules */
		struct ieee80211_replay_event iev;

		IEEE80211_ADDR_COPY(iev.iev_dst, wh->i_addr1);
		IEEE80211_ADDR_COPY(iev.iev_src, wh->i_addr2);
		iev.iev_cipher = k->wk_cipher->ic_cipher;
		if (k->wk_rxkeyix != IEEE80211_KEYIX_NONE)
			iev.iev_keyix = k->wk_rxkeyix;
		else
			iev.iev_keyix = k->wk_keyix;
		iev.iev_keyrsc = k->wk_keyrsc[tid];
		iev.iev_rsc = rsc;
		CURVNET_SET(ifp->if_vnet);
		rt_ieee80211msg(ifp, RTM_IEEE80211_REPLAY, &iev, sizeof(iev));
		CURVNET_RESTORE();
	}
}