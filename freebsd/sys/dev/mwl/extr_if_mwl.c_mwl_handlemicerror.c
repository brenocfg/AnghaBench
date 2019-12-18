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
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211com {int dummy; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_vap; } ;
struct ieee80211_frame_min {int dummy; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 struct ieee80211_node* ieee80211_find_rxnode (struct ieee80211com*,struct ieee80211_frame_min const*) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_notify_michael_failure (int /*<<< orphan*/ ,struct ieee80211_frame const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwl_handlemicerror(struct ieee80211com *ic, const uint8_t *data)
{
	const struct ieee80211_frame *wh;
	struct ieee80211_node *ni;

	wh = (const struct ieee80211_frame *)(data + sizeof(uint16_t));
	ni = ieee80211_find_rxnode(ic, (const struct ieee80211_frame_min *) wh);
	if (ni != NULL) {
		ieee80211_notify_michael_failure(ni->ni_vap, wh, 0);
		ieee80211_free_node(ni);
	}
}