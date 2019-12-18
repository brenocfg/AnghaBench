#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211com {TYPE_2__* ic_csa_newchan; TYPE_1__* ic_bsschan; } ;
struct TYPE_4__ {int ic_flags; } ;
struct TYPE_3__ {int ic_flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_5GHZ ; 
 int IEEE80211_CHAN_HALF ; 
 int IEEE80211_CHAN_HT ; 
 int IEEE80211_CHAN_QUARTER ; 

__attribute__((used)) static int
isbandchange(struct ieee80211com *ic)
{
	return ((ic->ic_bsschan->ic_flags ^ ic->ic_csa_newchan->ic_flags) &
	    (IEEE80211_CHAN_2GHZ | IEEE80211_CHAN_5GHZ | IEEE80211_CHAN_HALF |
	     IEEE80211_CHAN_QUARTER | IEEE80211_CHAN_HT)) != 0;
}