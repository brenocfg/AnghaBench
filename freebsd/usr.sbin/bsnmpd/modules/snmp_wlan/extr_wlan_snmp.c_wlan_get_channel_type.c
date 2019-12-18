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
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_FHSS (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel*) ; 
 int WlanChannelType_dot11a ; 
 int WlanChannelType_dot11b ; 
 int WlanChannelType_dot11g ; 
 int WlanChannelType_fhss ; 
 int WlanChannelType_fiveMHz ; 
 int WlanChannelType_ht ; 
 int WlanChannelType_tenMHz ; 
 int WlanChannelType_turbo ; 

__attribute__((used)) static int32_t
wlan_get_channel_type(struct ieee80211_channel *c)
{
	if (IEEE80211_IS_CHAN_FHSS(c))
		return (WlanChannelType_fhss);
	if (IEEE80211_IS_CHAN_A(c))
		return (WlanChannelType_dot11a);
	if (IEEE80211_IS_CHAN_B(c))
		return (WlanChannelType_dot11b);
	if (IEEE80211_IS_CHAN_ANYG(c))
		return (WlanChannelType_dot11g);
	if (IEEE80211_IS_CHAN_HALF(c))
		return (WlanChannelType_tenMHz);
	if (IEEE80211_IS_CHAN_QUARTER(c))
		return (WlanChannelType_fiveMHz);
	if (IEEE80211_IS_CHAN_TURBO(c))
		return (WlanChannelType_turbo);
	if (IEEE80211_IS_CHAN_HT(c))
		return (WlanChannelType_ht);

	return (-1);
}