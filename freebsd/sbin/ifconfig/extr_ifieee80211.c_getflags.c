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
 int IEEE80211_NODE_AMPDU_RX ; 
 int IEEE80211_NODE_AMPDU_TX ; 
 int IEEE80211_NODE_AMSDU_RX ; 
 int IEEE80211_NODE_AMSDU_TX ; 
 int IEEE80211_NODE_AUTH ; 
 int IEEE80211_NODE_ERP ; 
 int IEEE80211_NODE_HT ; 
 int IEEE80211_NODE_HTCOMPAT ; 
 int IEEE80211_NODE_MIMO_PS ; 
 int IEEE80211_NODE_MIMO_RTS ; 
 int IEEE80211_NODE_PWR_MGT ; 
 int IEEE80211_NODE_QOS ; 
 int IEEE80211_NODE_RIFS ; 
 int IEEE80211_NODE_SGI20 ; 
 int IEEE80211_NODE_SGI40 ; 
 int IEEE80211_NODE_TSN ; 
 int IEEE80211_NODE_VHT ; 
 int IEEE80211_NODE_WPS ; 

__attribute__((used)) static const char *
getflags(int flags)
{
	static char flagstring[32];
	char *cp = flagstring;

	if (flags & IEEE80211_NODE_AUTH)
		*cp++ = 'A';
	if (flags & IEEE80211_NODE_QOS)
		*cp++ = 'Q';
	if (flags & IEEE80211_NODE_ERP)
		*cp++ = 'E';
	if (flags & IEEE80211_NODE_PWR_MGT)
		*cp++ = 'P';
	if (flags & IEEE80211_NODE_HT) {
		*cp++ = 'H';
		if (flags & IEEE80211_NODE_HTCOMPAT)
			*cp++ = '+';
	}
	if (flags & IEEE80211_NODE_VHT)
		*cp++ = 'V';
	if (flags & IEEE80211_NODE_WPS)
		*cp++ = 'W';
	if (flags & IEEE80211_NODE_TSN)
		*cp++ = 'N';
	if (flags & IEEE80211_NODE_AMPDU_TX)
		*cp++ = 'T';
	if (flags & IEEE80211_NODE_AMPDU_RX)
		*cp++ = 'R';
	if (flags & IEEE80211_NODE_MIMO_PS) {
		*cp++ = 'M';
		if (flags & IEEE80211_NODE_MIMO_RTS)
			*cp++ = '+';
	}
	if (flags & IEEE80211_NODE_RIFS)
		*cp++ = 'I';
	if (flags & IEEE80211_NODE_SGI40) {
		*cp++ = 'S';
		if (flags & IEEE80211_NODE_SGI20)
			*cp++ = '+';
	} else if (flags & IEEE80211_NODE_SGI20)
		*cp++ = 's';
	if (flags & IEEE80211_NODE_AMSDU_TX)
		*cp++ = 't';
	if (flags & IEEE80211_NODE_AMSDU_RX)
		*cp++ = 'r';
	*cp = '\0';
	return flagstring;
}