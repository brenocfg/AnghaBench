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
#define  IEEE80211_REASON_4WAY_HANDSHAKE_TIMEOUT 150 
#define  IEEE80211_REASON_802_1X_AUTH_FAILED 149 
#define  IEEE80211_REASON_AKMP_INVALID 148 
#define  IEEE80211_REASON_ASSOC_EXPIRE 147 
#define  IEEE80211_REASON_ASSOC_LEAVE 146 
#define  IEEE80211_REASON_ASSOC_NOT_AUTHED 145 
#define  IEEE80211_REASON_ASSOC_TOOMANY 144 
#define  IEEE80211_REASON_AUTH_EXPIRE 143 
#define  IEEE80211_REASON_AUTH_LEAVE 142 
#define  IEEE80211_REASON_CIPHER_SUITE_REJECTED 141 
#define  IEEE80211_REASON_DISASSOC_PWRCAP_BAD 140 
#define  IEEE80211_REASON_DISASSOC_SUPCHAN_BAD 139 
#define  IEEE80211_REASON_GROUP_CIPHER_INVALID 138 
#define  IEEE80211_REASON_GROUP_KEY_UPDATE_TIMEOUT 137 
#define  IEEE80211_REASON_IE_INVALID 136 
#define  IEEE80211_REASON_IE_IN_4WAY_DIFFERS 135 
#define  IEEE80211_REASON_INVALID_RSN_IE_CAP 134 
#define  IEEE80211_REASON_MIC_FAILURE 133 
#define  IEEE80211_REASON_NOT_ASSOCED 132 
#define  IEEE80211_REASON_NOT_AUTHED 131 
#define  IEEE80211_REASON_PAIRWISE_CIPHER_INVALID 130 
#define  IEEE80211_REASON_UNSPECIFIED 129 
#define  IEEE80211_REASON_UNSUPP_RSN_IE_VERSION 128 
 int nitems (char const**) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

void
setreason(char b[], size_t bs, int v)
{
    static const char *reasons[] = {
	[IEEE80211_REASON_UNSPECIFIED]		= "unspecified",
	[IEEE80211_REASON_AUTH_EXPIRE]		= "auth expire",
	[IEEE80211_REASON_AUTH_LEAVE]		= "auth leave",
	[IEEE80211_REASON_ASSOC_EXPIRE]		= "assoc expire",
	[IEEE80211_REASON_ASSOC_TOOMANY]	= "assoc toomany",
	[IEEE80211_REASON_NOT_AUTHED]		= "not authed",
	[IEEE80211_REASON_NOT_ASSOCED]		= "not assoced",
	[IEEE80211_REASON_ASSOC_LEAVE]		= "assoc leave",
	[IEEE80211_REASON_ASSOC_NOT_AUTHED]	= "assoc not authed",
	[IEEE80211_REASON_DISASSOC_PWRCAP_BAD]	= "disassoc pwrcap bad",
	[IEEE80211_REASON_DISASSOC_SUPCHAN_BAD]	= "disassoc supchan bad",
	[IEEE80211_REASON_IE_INVALID]		= "ie invalid",
	[IEEE80211_REASON_MIC_FAILURE]		= "mic failure",
	[IEEE80211_REASON_4WAY_HANDSHAKE_TIMEOUT]= "4-way handshake timeout",
	[IEEE80211_REASON_GROUP_KEY_UPDATE_TIMEOUT] = "group key update timeout",
	[IEEE80211_REASON_IE_IN_4WAY_DIFFERS]	= "ie in 4-way differs",
	[IEEE80211_REASON_GROUP_CIPHER_INVALID]	= "group cipher invalid",
	[IEEE80211_REASON_PAIRWISE_CIPHER_INVALID]= "pairwise cipher invalid",
	[IEEE80211_REASON_AKMP_INVALID]		= "akmp invalid",
	[IEEE80211_REASON_UNSUPP_RSN_IE_VERSION]= "unsupported rsn ie version",
	[IEEE80211_REASON_INVALID_RSN_IE_CAP]	= "invalid rsn ie cap",
	[IEEE80211_REASON_802_1X_AUTH_FAILED]	= "802.1x auth failed",
	[IEEE80211_REASON_CIPHER_SUITE_REJECTED]= "cipher suite rejected",
    };
    if (v < nitems(reasons) && reasons[v] != NULL)
	    snprintf(b, bs, "%s (%u)", reasons[v], v);
    else
	    snprintf(b, bs, "%u", v);
}