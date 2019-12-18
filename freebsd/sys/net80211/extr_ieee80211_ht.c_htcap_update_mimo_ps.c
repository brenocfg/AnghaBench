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
typedef  int uint16_t ;
struct ieee80211_node {int ni_flags; int ni_htcap; } ;

/* Variables and functions */
 int IEEE80211_HTCAP_SMPS ; 
#define  IEEE80211_HTCAP_SMPS_DYNAMIC 130 
#define  IEEE80211_HTCAP_SMPS_ENA 129 
#define  IEEE80211_HTCAP_SMPS_OFF 128 
 int IEEE80211_NODE_MIMO_PS ; 
 int IEEE80211_NODE_MIMO_RTS ; 

__attribute__((used)) static __inline int
htcap_update_mimo_ps(struct ieee80211_node *ni)
{
	uint16_t oflags = ni->ni_flags;

	switch (ni->ni_htcap & IEEE80211_HTCAP_SMPS) {
	case IEEE80211_HTCAP_SMPS_DYNAMIC:
		ni->ni_flags |= IEEE80211_NODE_MIMO_PS;
		ni->ni_flags |= IEEE80211_NODE_MIMO_RTS;
		break;
	case IEEE80211_HTCAP_SMPS_ENA:
		ni->ni_flags |= IEEE80211_NODE_MIMO_PS;
		ni->ni_flags &= ~IEEE80211_NODE_MIMO_RTS;
		break;
	case IEEE80211_HTCAP_SMPS_OFF:
	default:		/* disable on rx of reserved value */
		ni->ni_flags &= ~IEEE80211_NODE_MIMO_PS;
		ni->ni_flags &= ~IEEE80211_NODE_MIMO_RTS;
		break;
	}
	return (oflags ^ ni->ni_flags);
}