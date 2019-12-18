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
struct TYPE_2__ {int is_ampdu_rx_oor; } ;
struct ieee80211vap {TYPE_1__ iv_stats; } ;
struct ieee80211_rx_ampdu {int rxa_wnd; scalar_t__ rxa_qframes; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int ampdu_dispatch_slot (struct ieee80211_rx_ampdu*,struct ieee80211_node*,int) ; 

__attribute__((used)) static void
ampdu_rx_flush(struct ieee80211_node *ni, struct ieee80211_rx_ampdu *rap)
{
	struct ieee80211vap *vap = ni->ni_vap;
	int i, r;

	for (i = 0; i < rap->rxa_wnd; i++) {
		r = ampdu_dispatch_slot(rap, ni, i);
		if (r == 0)
			continue;
		vap->iv_stats.is_ampdu_rx_oor += r;

		if (rap->rxa_qframes == 0)
			break;
	}
}