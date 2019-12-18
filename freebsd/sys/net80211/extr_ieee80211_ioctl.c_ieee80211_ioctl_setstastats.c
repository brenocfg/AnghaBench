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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211vap {TYPE_1__* iv_ic; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_sta; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int IEEE80211_ADDR_LEN ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ieee80211_node* ieee80211_find_vap_node (int /*<<< orphan*/ *,struct ieee80211vap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ieee80211_ioctl_setstastats(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211_node *ni;
	uint8_t macaddr[IEEE80211_ADDR_LEN];
	int error;

	/*
	 * NB: we could copyin ieee80211req_sta_stats so apps
	 *     could make selective changes but that's overkill;
	 *     just clear all stats for now.
	 */
	if (ireq->i_len < IEEE80211_ADDR_LEN)
		return EINVAL;
	error = copyin(ireq->i_data, macaddr, IEEE80211_ADDR_LEN);
	if (error != 0)
		return error;
	ni = ieee80211_find_vap_node(&vap->iv_ic->ic_sta, vap, macaddr);
	if (ni == NULL)
		return ENOENT;
	/* XXX require ni_vap == vap? */
	memset(&ni->ni_stats, 0, sizeof(ni->ni_stats));
	ieee80211_free_node(ni);
	return 0;
}