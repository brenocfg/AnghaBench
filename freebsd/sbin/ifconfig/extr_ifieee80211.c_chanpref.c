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
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT20 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_PUREG (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT160 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT20 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT40 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT80 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT80_80 (struct ieee80211_channel const*) ; 

__attribute__((used)) static int
chanpref(const struct ieee80211_channel *c)
{
	if (IEEE80211_IS_CHAN_VHT160(c))
		return 80;
	if (IEEE80211_IS_CHAN_VHT80_80(c))
		return 75;
	if (IEEE80211_IS_CHAN_VHT80(c))
		return 70;
	if (IEEE80211_IS_CHAN_VHT40(c))
		return 60;
	if (IEEE80211_IS_CHAN_VHT20(c))
		return 50;
	if (IEEE80211_IS_CHAN_HT40(c))
		return 40;
	if (IEEE80211_IS_CHAN_HT20(c))
		return 30;
	if (IEEE80211_IS_CHAN_HALF(c))
		return 10;
	if (IEEE80211_IS_CHAN_QUARTER(c))
		return 5;
	if (IEEE80211_IS_CHAN_TURBO(c))
		return 25;
	if (IEEE80211_IS_CHAN_A(c))
		return 20;
	if (IEEE80211_IS_CHAN_G(c))
		return 20;
	if (IEEE80211_IS_CHAN_B(c))
		return 15;
	if (IEEE80211_IS_CHAN_PUREG(c))
		return 15;
	return 0;
}