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
 int IEEE80211_FC0_SUBTYPE_ASSOC_REQ ; 
 int IEEE80211_FC0_SUBTYPE_AUTH ; 
 int IEEE80211_FC0_SUBTYPE_DATA ; 
 int IEEE80211_FC0_SUBTYPE_PROBE_REQ ; 
 int IEEE80211_FC0_SUBTYPE_SHIFT ; 
 int atoi (char const*) ; 
 scalar_t__ equal (char const*,char*) ; 

int str2subtype(const char *subtype)
{
#define	equal(a,b)	(strcasecmp(a,b) == 0)
	if (equal(subtype, "preq") || equal(subtype, "probereq"))
		return IEEE80211_FC0_SUBTYPE_PROBE_REQ >>
		       IEEE80211_FC0_SUBTYPE_SHIFT;
	else if (equal(subtype, "auth"))
		return IEEE80211_FC0_SUBTYPE_AUTH >>
		       IEEE80211_FC0_SUBTYPE_SHIFT;
	else if (equal(subtype, "areq") || equal(subtype, "assocreq"))
		return IEEE80211_FC0_SUBTYPE_ASSOC_REQ >>
		       IEEE80211_FC0_SUBTYPE_SHIFT;
	else if (equal(subtype, "data"))
		return IEEE80211_FC0_SUBTYPE_DATA >>
		       IEEE80211_FC0_SUBTYPE_SHIFT;

	return atoi(subtype) & 0xf;
#undef equal
}