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
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_108A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_FHSS (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HTA (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HTG (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ST (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHTA (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHTG (struct ieee80211_channel const*) ; 
 int IEEE80211_MODE_11A ; 
 int IEEE80211_MODE_11B ; 
 int IEEE80211_MODE_11G ; 
 int IEEE80211_MODE_11NA ; 
 int IEEE80211_MODE_11NG ; 
 int IEEE80211_MODE_AUTO ; 
 int IEEE80211_MODE_FH ; 
 int IEEE80211_MODE_HALF ; 
 int IEEE80211_MODE_QUARTER ; 
 int IEEE80211_MODE_STURBO_A ; 
 int IEEE80211_MODE_TURBO_A ; 
 int IEEE80211_MODE_TURBO_G ; 
 int IEEE80211_MODE_VHT_2GHZ ; 
 int IEEE80211_MODE_VHT_5GHZ ; 

__attribute__((used)) static enum ieee80211_phymode
chan2mode(const struct ieee80211_channel *c)
{
	if (IEEE80211_IS_CHAN_VHTA(c))
		return IEEE80211_MODE_VHT_5GHZ;
	if (IEEE80211_IS_CHAN_VHTG(c))
		return IEEE80211_MODE_VHT_2GHZ;
	if (IEEE80211_IS_CHAN_HTA(c))
		return IEEE80211_MODE_11NA;
	if (IEEE80211_IS_CHAN_HTG(c))
		return IEEE80211_MODE_11NG;
	if (IEEE80211_IS_CHAN_108A(c))
		return IEEE80211_MODE_TURBO_A;
	if (IEEE80211_IS_CHAN_108G(c))
		return IEEE80211_MODE_TURBO_G;
	if (IEEE80211_IS_CHAN_ST(c))
		return IEEE80211_MODE_STURBO_A;
	if (IEEE80211_IS_CHAN_FHSS(c))
		return IEEE80211_MODE_FH;
	if (IEEE80211_IS_CHAN_HALF(c))
		return IEEE80211_MODE_HALF;
	if (IEEE80211_IS_CHAN_QUARTER(c))
		return IEEE80211_MODE_QUARTER;
	if (IEEE80211_IS_CHAN_A(c))
		return IEEE80211_MODE_11A;
	if (IEEE80211_IS_CHAN_ANYG(c))
		return IEEE80211_MODE_11G;
	if (IEEE80211_IS_CHAN_B(c))
		return IEEE80211_MODE_11B;
	return IEEE80211_MODE_AUTO;
}