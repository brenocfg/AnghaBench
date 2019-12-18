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
typedef  int /*<<< orphan*/  vlan ;
struct ieee80211vap {int /*<<< orphan*/  iv_bss; TYPE_1__* iv_ic; } ;
struct ieee80211req_sta_vlan {int /*<<< orphan*/  sv_vlan; int /*<<< orphan*/  sv_macaddr; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_vlan; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_sta; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,struct ieee80211req_sta_vlan*,int) ; 
 struct ieee80211_node* ieee80211_find_vap_node (int /*<<< orphan*/ *,struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_ref_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zerobssid ; 

__attribute__((used)) static int
ieee80211_ioctl_setstavlan(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211_node *ni;
	struct ieee80211req_sta_vlan vlan;
	int error;

	if (ireq->i_len != sizeof(vlan))
		return EINVAL;
	error = copyin(ireq->i_data, &vlan, sizeof(vlan));
	if (error != 0)
		return error;
	if (!IEEE80211_ADDR_EQ(vlan.sv_macaddr, zerobssid)) {
		ni = ieee80211_find_vap_node(&vap->iv_ic->ic_sta, vap,
		    vlan.sv_macaddr);
		if (ni == NULL)
			return ENOENT;
	} else
		ni = ieee80211_ref_node(vap->iv_bss);
	ni->ni_vlan = vlan.sv_vlan;
	ieee80211_free_node(ni);
	return error;
}