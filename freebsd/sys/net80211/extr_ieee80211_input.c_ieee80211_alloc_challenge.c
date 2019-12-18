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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211_node {int /*<<< orphan*/ * ni_challenge; int /*<<< orphan*/  ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHALLENGE_LEN ; 
 scalar_t__ IEEE80211_MALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_MSG_AUTH ; 
 int IEEE80211_MSG_DEBUG ; 
 int /*<<< orphan*/  IEEE80211_M_NOWAIT ; 
 int /*<<< orphan*/  IEEE80211_NOTE (int /*<<< orphan*/ ,int,struct ieee80211_node*,char*,char*) ; 
 int /*<<< orphan*/  M_80211_NODE ; 

int
ieee80211_alloc_challenge(struct ieee80211_node *ni)
{
	if (ni->ni_challenge == NULL)
		ni->ni_challenge = (uint32_t *)
		    IEEE80211_MALLOC(IEEE80211_CHALLENGE_LEN,
		      M_80211_NODE, IEEE80211_M_NOWAIT);
	if (ni->ni_challenge == NULL) {
		IEEE80211_NOTE(ni->ni_vap,
		    IEEE80211_MSG_DEBUG | IEEE80211_MSG_AUTH, ni,
		    "%s", "shared key challenge alloc failed");
		/* XXX statistic */
	}
	return (ni->ni_challenge != NULL);
}