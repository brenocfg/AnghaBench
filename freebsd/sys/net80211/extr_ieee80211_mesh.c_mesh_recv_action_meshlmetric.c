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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_meshlmetric_ie {int lm_flags; int /*<<< orphan*/  lm_metric; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_MESH ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESH_LMETRIC ; 
 int IEEE80211_MESH_LMETRIC_FLAGS_REQ ; 
 int /*<<< orphan*/  ieee80211_send_action (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_meshlmetric_ie*) ; 
 int /*<<< orphan*/  mesh_airtime_calc (struct ieee80211_node*) ; 

__attribute__((used)) static int
mesh_recv_action_meshlmetric(struct ieee80211_node *ni,
	const struct ieee80211_frame *wh,
	const uint8_t *frm, const uint8_t *efrm)
{
	const struct ieee80211_meshlmetric_ie *ie =
	    (const struct ieee80211_meshlmetric_ie *)
	    (frm+2); /* action + code */
	struct ieee80211_meshlmetric_ie lm_rep;
	
	if (ie->lm_flags & IEEE80211_MESH_LMETRIC_FLAGS_REQ) {
		lm_rep.lm_flags = 0;
		lm_rep.lm_metric = mesh_airtime_calc(ni);
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_MESH,
		    IEEE80211_ACTION_MESH_LMETRIC,
		    &lm_rep);
	}
	/* XXX: else do nothing for now */
	return 0;
}