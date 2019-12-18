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
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_DATA ; 
 int IEEE80211_FC0_TYPE_MGT ; 
 int IEEE80211_FC0_TYPE_SHIFT ; 
 int atoi (char const*) ; 
 scalar_t__ equal (char const*,char*) ; 

int str2type(const char *type)
{
#define	equal(a,b)	(strcasecmp(a,b) == 0)
	if (equal(type, "mgt"))
		return IEEE80211_FC0_TYPE_MGT >> IEEE80211_FC0_TYPE_SHIFT;
	else if (equal(type, "ctl"))
		return IEEE80211_FC0_TYPE_CTL >> IEEE80211_FC0_TYPE_SHIFT;
	else if (equal(type, "data"))
		return IEEE80211_FC0_TYPE_DATA >> IEEE80211_FC0_TYPE_SHIFT;

	return atoi(type) & 3;
#undef equal
}