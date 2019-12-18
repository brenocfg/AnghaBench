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
struct ieee80211vap {int /*<<< orphan*/  iv_roaming; TYPE_1__* iv_bss; } ;
struct ieee80211_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ni_macaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_AUTH ; 
#define  IEEE80211_REASON_ASSOC_EXPIRE 134 
#define  IEEE80211_REASON_ASSOC_LEAVE 133 
#define  IEEE80211_REASON_ASSOC_NOT_AUTHED 132 
#define  IEEE80211_REASON_NOT_ASSOCED 131 
#define  IEEE80211_REASON_NOT_AUTHED 130 
 int /*<<< orphan*/  IEEE80211_ROAMING_AUTO ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int /*<<< orphan*/ ,int) ; 
#define  IEEE80211_STATUS_SUCCESS 129 
#define  IEEE80211_STATUS_TIMEOUT 128 
 int /*<<< orphan*/  ieee80211_check_scan_current (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_scan_assoc_fail (struct ieee80211vap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sta_authretry(struct ieee80211vap *vap, struct ieee80211_node *ni, int reason)
{
	switch (reason) {
	case IEEE80211_STATUS_SUCCESS:		/* NB: MLME assoc */
	case IEEE80211_STATUS_TIMEOUT:
	case IEEE80211_REASON_ASSOC_EXPIRE:
	case IEEE80211_REASON_NOT_AUTHED:
	case IEEE80211_REASON_NOT_ASSOCED:
	case IEEE80211_REASON_ASSOC_LEAVE:
	case IEEE80211_REASON_ASSOC_NOT_AUTHED:
		IEEE80211_SEND_MGMT(ni, IEEE80211_FC0_SUBTYPE_AUTH, 1);
		break;
	default:
		ieee80211_scan_assoc_fail(vap, vap->iv_bss->ni_macaddr, reason);
		if (vap->iv_roaming == IEEE80211_ROAMING_AUTO)
			ieee80211_check_scan_current(vap);
		break;
	}
}