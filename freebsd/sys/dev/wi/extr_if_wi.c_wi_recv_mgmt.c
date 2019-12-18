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
struct mbuf {int dummy; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_rx_stats {int dummy; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wv_recv_mgmt ) (struct ieee80211_node*,struct mbuf*,int,struct ieee80211_rx_stats const*,int,int) ;} ;

/* Variables and functions */
#define  IEEE80211_FC0_SUBTYPE_ASSOC_RESP 130 
#define  IEEE80211_FC0_SUBTYPE_AUTH 129 
#define  IEEE80211_FC0_SUBTYPE_REASSOC_RESP 128 
 TYPE_1__* WI_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,struct mbuf*,int,struct ieee80211_rx_stats const*,int,int) ; 

__attribute__((used)) static void
wi_recv_mgmt(struct ieee80211_node *ni, struct mbuf *m,
	int subtype, const struct ieee80211_rx_stats *rxs, int rssi, int nf)
{
	struct ieee80211vap *vap = ni->ni_vap;

	switch (subtype) {
	case IEEE80211_FC0_SUBTYPE_AUTH:
	case IEEE80211_FC0_SUBTYPE_ASSOC_RESP:
	case IEEE80211_FC0_SUBTYPE_REASSOC_RESP:
		/* NB: filter frames that trigger state changes */
		return;
	}
	WI_VAP(vap)->wv_recv_mgmt(ni, m, subtype, rxs, rssi, nf);
}