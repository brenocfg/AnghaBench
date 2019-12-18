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
typedef  scalar_t__ uint8_t ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_ie_htinfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ const IEEE80211_ELEMID_VENDOR ; 
 int /*<<< orphan*/  htinfo_parse (struct ieee80211_node*,struct ieee80211_ie_htinfo const*) ; 

void
ieee80211_parse_htinfo(struct ieee80211_node *ni, const uint8_t *ie)
{
	if (ie[0] == IEEE80211_ELEMID_VENDOR)
		ie += 4;
	htinfo_parse(ni, (const struct ieee80211_ie_htinfo *) ie);
}