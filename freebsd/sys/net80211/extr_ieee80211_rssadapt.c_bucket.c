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

/* Variables and functions */
 int IEEE80211_RSSADAPT_BKT0 ; 
 int IEEE80211_RSSADAPT_BKTPOWER ; 
 int IEEE80211_RSSADAPT_BKTS ; 

__attribute__((used)) static __inline int
bucket(int pktlen)
{
	int i, top, thridx;

	for (i = 0, top = IEEE80211_RSSADAPT_BKT0;
	     i < IEEE80211_RSSADAPT_BKTS;
	     i++, top <<= IEEE80211_RSSADAPT_BKTPOWER) {
		thridx = i;
		if (pktlen <= top)
			break;
	}
	return thridx;
}