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
#define  IEEE80211_STATUS_AKMP_INVALID 153 
#define  IEEE80211_STATUS_ALG 152 
#define  IEEE80211_STATUS_BASIC_RATE 151 
#define  IEEE80211_STATUS_CAPINFO 150 
#define  IEEE80211_STATUS_CA_REQUIRED 149 
#define  IEEE80211_STATUS_CHALLENGE 148 
#define  IEEE80211_STATUS_CIPHER_SUITE_REJECTED 147 
#define  IEEE80211_STATUS_DSSSOFDM_REQUIRED 146 
#define  IEEE80211_STATUS_GROUP_CIPHER_INVALID 145 
#define  IEEE80211_STATUS_INVALID_IE 144 
#define  IEEE80211_STATUS_INVALID_RSN_IE_CAP 143 
#define  IEEE80211_STATUS_NOT_ASSOCED 142 
#define  IEEE80211_STATUS_OTHER 141 
#define  IEEE80211_STATUS_PAIRWISE_CIPHER_INVALID 140 
#define  IEEE80211_STATUS_PBCC_REQUIRED 139 
#define  IEEE80211_STATUS_PWRCAP_REQUIRED 138 
#define  IEEE80211_STATUS_SEQUENCE 137 
#define  IEEE80211_STATUS_SHORTSLOT_REQUIRED 136 
#define  IEEE80211_STATUS_SPECMGMT_REQUIRED 135 
#define  IEEE80211_STATUS_SP_REQUIRED 134 
#define  IEEE80211_STATUS_SUCCESS 133 
#define  IEEE80211_STATUS_SUPCHAN_REQUIRED 132 
#define  IEEE80211_STATUS_TIMEOUT 131 
#define  IEEE80211_STATUS_TOOMANY 130 
#define  IEEE80211_STATUS_UNSPECIFIED 129 
#define  IEEE80211_STATUS_UNSUPP_RSN_IE_VERSION 128 
 int nitems (char const**) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

void
setstatus(char b[], size_t bs, int v)
{
    static const char *status[] = {
	[IEEE80211_STATUS_SUCCESS]		= "success",
	[IEEE80211_STATUS_UNSPECIFIED]		= "unspecified",
	[IEEE80211_STATUS_CAPINFO]		= "capinfo",
	[IEEE80211_STATUS_NOT_ASSOCED]		= "not assoced",
	[IEEE80211_STATUS_OTHER]		= "other",
	[IEEE80211_STATUS_ALG]			= "algorithm",
	[IEEE80211_STATUS_SEQUENCE]		= "sequence",
	[IEEE80211_STATUS_CHALLENGE]		= "challenge",
	[IEEE80211_STATUS_TIMEOUT]		= "timeout",
	[IEEE80211_STATUS_TOOMANY]		= "toomany",
	[IEEE80211_STATUS_BASIC_RATE]		= "basic rate",
	[IEEE80211_STATUS_SP_REQUIRED]		= "sp required",
	[IEEE80211_STATUS_PBCC_REQUIRED]	= "pbcc required",
	[IEEE80211_STATUS_CA_REQUIRED]		= "ca required",
	[IEEE80211_STATUS_SPECMGMT_REQUIRED]	= "specmgmt required",
	[IEEE80211_STATUS_PWRCAP_REQUIRED]	= "pwrcap required",
	[IEEE80211_STATUS_SUPCHAN_REQUIRED]	= "supchan required",
	[IEEE80211_STATUS_SHORTSLOT_REQUIRED]	= "shortslot required",
	[IEEE80211_STATUS_DSSSOFDM_REQUIRED]	= "dsssofdm required",
	[IEEE80211_STATUS_INVALID_IE]		= "invalid ie",
	[IEEE80211_STATUS_GROUP_CIPHER_INVALID]	= "group cipher invalid",
	[IEEE80211_STATUS_PAIRWISE_CIPHER_INVALID]= "pairwise cipher invalid",
	[IEEE80211_STATUS_AKMP_INVALID]		= "akmp invalid",
	[IEEE80211_STATUS_UNSUPP_RSN_IE_VERSION]= "unsupported rsn ie version",
	[IEEE80211_STATUS_INVALID_RSN_IE_CAP]	= "invalid rsn ie cap",
	[IEEE80211_STATUS_CIPHER_SUITE_REJECTED]= "cipher suite rejected",
    };
    if (v < nitems(status) && status[v] != NULL)
	    snprintf(b, bs, "%s (%u)", status[v], v);
    else
	    snprintf(b, bs, "%u", v);
}