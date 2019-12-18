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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_ie_htinfo {int hi_byte2; } ;

/* Variables and functions */
 int IEEE80211_HTINFO_OPMODE ; 
 int IEEE80211_HTINFO_OPMODE_MIXED ; 

__attribute__((used)) static __inline int
ishtmixed(const uint8_t *ie)
{
	const struct ieee80211_ie_htinfo *ht =
	    (const struct ieee80211_ie_htinfo *) ie;
	return (ht->hi_byte2 & IEEE80211_HTINFO_OPMODE) ==
	    IEEE80211_HTINFO_OPMODE_MIXED;
}