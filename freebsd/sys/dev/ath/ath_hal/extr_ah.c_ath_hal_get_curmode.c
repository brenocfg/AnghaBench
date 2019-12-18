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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 int HAL_MODE_11A ; 
 int HAL_MODE_11B ; 
 int HAL_MODE_11G ; 
 int HAL_MODE_11NA_HT20 ; 
 int HAL_MODE_11NA_HT40MINUS ; 
 int HAL_MODE_11NA_HT40PLUS ; 
 int HAL_MODE_11NG_HT20 ; 
 int HAL_MODE_11NG_HT40MINUS ; 
 int HAL_MODE_11NG_HT40PLUS ; 
 int HAL_MODE_TURBO ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT20 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40D (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40U (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 

int
ath_hal_get_curmode(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	/*
	 * Pick a default mode at bootup. A channel change is inevitable.
	 */
	if (!chan)
		return HAL_MODE_11NG_HT20;

	if (IEEE80211_IS_CHAN_TURBO(chan))
		return HAL_MODE_TURBO;

	/* check for NA_HT before plain A, since IS_CHAN_A includes NA_HT */
	if (IEEE80211_IS_CHAN_5GHZ(chan) && IEEE80211_IS_CHAN_HT20(chan))
		return HAL_MODE_11NA_HT20;
	if (IEEE80211_IS_CHAN_5GHZ(chan) && IEEE80211_IS_CHAN_HT40U(chan))
		return HAL_MODE_11NA_HT40PLUS;
	if (IEEE80211_IS_CHAN_5GHZ(chan) && IEEE80211_IS_CHAN_HT40D(chan))
		return HAL_MODE_11NA_HT40MINUS;
	if (IEEE80211_IS_CHAN_A(chan))
		return HAL_MODE_11A;

	/* check for NG_HT before plain G, since IS_CHAN_G includes NG_HT */
	if (IEEE80211_IS_CHAN_2GHZ(chan) && IEEE80211_IS_CHAN_HT20(chan))
		return HAL_MODE_11NG_HT20;
	if (IEEE80211_IS_CHAN_2GHZ(chan) && IEEE80211_IS_CHAN_HT40U(chan))
		return HAL_MODE_11NG_HT40PLUS;
	if (IEEE80211_IS_CHAN_2GHZ(chan) && IEEE80211_IS_CHAN_HT40D(chan))
		return HAL_MODE_11NG_HT40MINUS;

	/*
	 * XXX For FreeBSD, will this work correctly given the DYN
	 * chan mode (OFDM+CCK dynamic) ? We have pure-G versions DYN-BG..
	 */
	if (IEEE80211_IS_CHAN_G(chan))
		return HAL_MODE_11G;
	if (IEEE80211_IS_CHAN_B(chan))
		return HAL_MODE_11B;

	HALASSERT(0);
	return HAL_MODE_11NG_HT20;
}