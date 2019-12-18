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
struct rssiinfo {int /*<<< orphan*/  rssi_total; int /*<<< orphan*/  rssi_samples; } ;
struct ieee80211vap {TYPE_1__* iv_ic; } ;
struct ieee80211_node {scalar_t__ ni_associd; struct ieee80211vap* ni_vap; } ;
typedef  scalar_t__ int8_t ;
struct TYPE_2__ {scalar_t__ (* ic_node_getrssi ) (struct ieee80211_node*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct ieee80211_node*) ; 

__attribute__((used)) static void
get_hostap_rssi(void *arg, struct ieee80211_node *ni)
{
	struct rssiinfo *info = arg;
	struct ieee80211vap *vap = ni->ni_vap;
	int8_t rssi;

	/* only associated stations */
	if (ni->ni_associd == 0)
		return;
	rssi = vap->iv_ic->ic_node_getrssi(ni);
	if (rssi != 0) {
		info->rssi_samples++;
		info->rssi_total += rssi;
	}
}