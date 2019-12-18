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
struct ieee80211com {void** ic_vattach; } ;

/* Variables and functions */
 size_t IEEE80211_M_AHDEMO ; 
 size_t IEEE80211_M_IBSS ; 
 void* adhoc_vattach ; 

void
ieee80211_adhoc_attach(struct ieee80211com *ic)
{
	ic->ic_vattach[IEEE80211_M_IBSS] = adhoc_vattach;
	ic->ic_vattach[IEEE80211_M_AHDEMO] = adhoc_vattach;
}