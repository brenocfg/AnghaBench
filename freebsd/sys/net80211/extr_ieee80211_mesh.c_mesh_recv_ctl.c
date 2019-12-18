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
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
#define  IEEE80211_FC0_SUBTYPE_BAR 128 
 int /*<<< orphan*/  ieee80211_recv_bar (struct ieee80211_node*,struct mbuf*) ; 

__attribute__((used)) static void
mesh_recv_ctl(struct ieee80211_node *ni, struct mbuf *m, int subtype)
{

	switch (subtype) {
	case IEEE80211_FC0_SUBTYPE_BAR:
		ieee80211_recv_bar(ni, m);
		break;
	}
}