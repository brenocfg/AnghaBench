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
struct ieee80211_frame {int* i_fc; } ;

/* Variables and functions */
 int IEEE80211_FC0_SUBTYPE_ACTION ; 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 int IEEE80211_FC0_TYPE_MGT ; 

__attribute__((used)) static int
ieee80211_is_action(struct ieee80211_frame *wh)
{
	/* Type: Management frame? */
	if ((wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) !=
	    IEEE80211_FC0_TYPE_MGT)
		return 0;

	/* Subtype: Action frame? */
	if ((wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) !=
	    IEEE80211_FC0_SUBTYPE_ACTION)
		return 0;

	return 1;
}