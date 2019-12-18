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
typedef  int /*<<< orphan*/  iename_buf ;

/* Variables and functions */
#define  IEEE80211_ELEMID_BSSLOAD 150 
#define  IEEE80211_ELEMID_CCKM 149 
#define  IEEE80211_ELEMID_CFPARMS 148 
#define  IEEE80211_ELEMID_CHALLENGE 147 
#define  IEEE80211_ELEMID_CSA 146 
#define  IEEE80211_ELEMID_EXTCAP 145 
#define  IEEE80211_ELEMID_FHPARMS 144 
#define  IEEE80211_ELEMID_IBSSDFS 143 
#define  IEEE80211_ELEMID_IBSSPARMS 142 
#define  IEEE80211_ELEMID_MEASREP 141 
#define  IEEE80211_ELEMID_MEASREQ 140 
#define  IEEE80211_ELEMID_MOBILITY_DOMAIN 139 
#define  IEEE80211_ELEMID_OVERLAP_BSS_SCAN_PARAM 138 
#define  IEEE80211_ELEMID_PWRCAP 137 
#define  IEEE80211_ELEMID_PWRCNSTR 136 
#define  IEEE80211_ELEMID_QUIET 135 
#define  IEEE80211_ELEMID_RESERVED_47 134 
#define  IEEE80211_ELEMID_RRM_ENACAPS 133 
#define  IEEE80211_ELEMID_SUPPCHAN 132 
#define  IEEE80211_ELEMID_TIM 131 
#define  IEEE80211_ELEMID_TPC 130 
#define  IEEE80211_ELEMID_TPCREP 129 
#define  IEEE80211_ELEMID_TPCREQ 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
iename(int elemid)
{
	static char iename_buf[64];
	switch (elemid) {
	case IEEE80211_ELEMID_FHPARMS:	return " FHPARMS";
	case IEEE80211_ELEMID_CFPARMS:	return " CFPARMS";
	case IEEE80211_ELEMID_TIM:	return " TIM";
	case IEEE80211_ELEMID_IBSSPARMS:return " IBSSPARMS";
	case IEEE80211_ELEMID_BSSLOAD:	return " BSSLOAD";
	case IEEE80211_ELEMID_CHALLENGE:return " CHALLENGE";
	case IEEE80211_ELEMID_PWRCNSTR:	return " PWRCNSTR";
	case IEEE80211_ELEMID_PWRCAP:	return " PWRCAP";
	case IEEE80211_ELEMID_TPCREQ:	return " TPCREQ";
	case IEEE80211_ELEMID_TPCREP:	return " TPCREP";
	case IEEE80211_ELEMID_SUPPCHAN:	return " SUPPCHAN";
	case IEEE80211_ELEMID_CSA:	return " CSA";
	case IEEE80211_ELEMID_MEASREQ:	return " MEASREQ";
	case IEEE80211_ELEMID_MEASREP:	return " MEASREP";
	case IEEE80211_ELEMID_QUIET:	return " QUIET";
	case IEEE80211_ELEMID_IBSSDFS:	return " IBSSDFS";
	case IEEE80211_ELEMID_RESERVED_47:
					return " RESERVED_47";
	case IEEE80211_ELEMID_MOBILITY_DOMAIN:
					return " MOBILITY_DOMAIN";
	case IEEE80211_ELEMID_RRM_ENACAPS:
					return " RRM_ENCAPS";
	case IEEE80211_ELEMID_OVERLAP_BSS_SCAN_PARAM:
					return " OVERLAP_BSS";
	case IEEE80211_ELEMID_TPC:	return " TPC";
	case IEEE80211_ELEMID_CCKM:	return " CCKM";
	case IEEE80211_ELEMID_EXTCAP:	return " EXTCAP";
	}
	snprintf(iename_buf, sizeof(iename_buf), " UNKNOWN_ELEMID_%d",
	    elemid);
	return (const char *) iename_buf;
}