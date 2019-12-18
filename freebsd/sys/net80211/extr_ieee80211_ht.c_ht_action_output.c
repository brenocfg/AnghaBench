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
struct ieee80211_node {int /*<<< orphan*/  ni_txpower; TYPE_1__* ni_txparms; } ;
struct ieee80211_bpf_params {int /*<<< orphan*/  ibp_power; int /*<<< orphan*/  ibp_try0; int /*<<< orphan*/  ibp_rate0; int /*<<< orphan*/  ibp_pri; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_2__ {int /*<<< orphan*/  maxretry; int /*<<< orphan*/  mgmtrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_ACTION ; 
 int /*<<< orphan*/  WME_AC_VO ; 
 int ieee80211_mgmt_output (struct ieee80211_node*,struct mbuf*,int /*<<< orphan*/ ,struct ieee80211_bpf_params*) ; 
 int /*<<< orphan*/  memset (struct ieee80211_bpf_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ht_action_output(struct ieee80211_node *ni, struct mbuf *m)
{
	struct ieee80211_bpf_params params;

	memset(&params, 0, sizeof(params));
	params.ibp_pri = WME_AC_VO;
	params.ibp_rate0 = ni->ni_txparms->mgmtrate;
	/* NB: we know all frames are unicast */
	params.ibp_try0 = ni->ni_txparms->maxretry;
	params.ibp_power = ni->ni_txpower;
	return ieee80211_mgmt_output(ni, m, IEEE80211_FC0_SUBTYPE_ACTION,
	     &params);
}