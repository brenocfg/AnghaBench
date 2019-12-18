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
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_108A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ST (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT (struct ieee80211_channel const*) ; 

char
ieee80211_channel_type_char(const struct ieee80211_channel *c)
{
	if (IEEE80211_IS_CHAN_ST(c))
		return 'S';
	if (IEEE80211_IS_CHAN_108A(c))
		return 'T';
	if (IEEE80211_IS_CHAN_108G(c))
		return 'G';
	if (IEEE80211_IS_CHAN_VHT(c))
		return 'v';
	if (IEEE80211_IS_CHAN_HT(c))
		return 'n';
	if (IEEE80211_IS_CHAN_A(c))
		return 'a';
	if (IEEE80211_IS_CHAN_ANYG(c))
		return 'g';
	if (IEEE80211_IS_CHAN_B(c))
		return 'b';
	return 'f';
}