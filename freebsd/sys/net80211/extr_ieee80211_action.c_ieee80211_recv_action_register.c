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
typedef  int /*<<< orphan*/  ieee80211_recv_action_func ;

/* Variables and functions */
 int EINVAL ; 
#define  IEEE80211_ACTION_CAT_BA 133 
#define  IEEE80211_ACTION_CAT_HT 132 
#define  IEEE80211_ACTION_CAT_MESH 131 
#define  IEEE80211_ACTION_CAT_SELF_PROT 130 
#define  IEEE80211_ACTION_CAT_VENDOR 129 
#define  IEEE80211_ACTION_CAT_VHT 128 
 int /*<<< orphan*/ ** ba_recv_action ; 
 int /*<<< orphan*/ ** ht_recv_action ; 
 int /*<<< orphan*/ ** meshaction_recv_action ; 
 int /*<<< orphan*/ ** meshpl_recv_action ; 
 int nitems (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** vendor_recv_action ; 
 int /*<<< orphan*/ ** vht_recv_action ; 

int
ieee80211_recv_action_register(int cat, int act, ieee80211_recv_action_func *f)
{
	switch (cat) {
	case IEEE80211_ACTION_CAT_BA:
		if (act >= nitems(ba_recv_action))
			break;
		ba_recv_action[act] = f;
		return 0;
	case IEEE80211_ACTION_CAT_HT:
		if (act >= nitems(ht_recv_action))
			break;
		ht_recv_action[act] = f;
		return 0;
	case IEEE80211_ACTION_CAT_SELF_PROT:
		if (act >= nitems(meshpl_recv_action))
			break;
		meshpl_recv_action[act] = f;
		return 0;
	case IEEE80211_ACTION_CAT_MESH:
		if (act >= nitems(meshaction_recv_action))
			break;
		meshaction_recv_action[act] = f;
		return 0;
	case IEEE80211_ACTION_CAT_VENDOR:
		if (act >= nitems(vendor_recv_action))
			break;
		vendor_recv_action[act] = f;
		return 0;
	case IEEE80211_ACTION_CAT_VHT:
		if (act >= nitems(vht_recv_action))
			break;
		vht_recv_action[act] = f;
		return 0;
	}
	return EINVAL;
}