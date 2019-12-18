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
struct ieee80211_node {TYPE_1__* ni_vap; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iv_recv_pspoll ) (struct ieee80211_node*,struct mbuf*) ;} ;

/* Variables and functions */
#define  IEEE80211_FC0_SUBTYPE_BAR 129 
#define  IEEE80211_FC0_SUBTYPE_PS_POLL 128 
 int /*<<< orphan*/  ieee80211_recv_bar (struct ieee80211_node*,struct mbuf*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,struct mbuf*) ; 

__attribute__((used)) static void
hostap_recv_ctl(struct ieee80211_node *ni, struct mbuf *m, int subtype)
{
	switch (subtype) {
	case IEEE80211_FC0_SUBTYPE_PS_POLL:
		ni->ni_vap->iv_recv_pspoll(ni, m);
		break;
	case IEEE80211_FC0_SUBTYPE_BAR:
		ieee80211_recv_bar(ni, m);
		break;
	}
}