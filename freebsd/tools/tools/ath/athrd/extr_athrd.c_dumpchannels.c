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
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; int /*<<< orphan*/  ic_flags; } ;
struct ath_hal {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_4MS (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_DFS (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_PASSIVE (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  ath_hal_mhz2ieee (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dopassive ; 
 scalar_t__ is4ms ; 
 scalar_t__ isdfs ; 
 int /*<<< orphan*/  n ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* sep ; 
 scalar_t__ showchannels ; 
 int tolower (int) ; 

__attribute__((used)) static void
dumpchannels(struct ath_hal *ah, int nc,
	const struct ieee80211_channel *chans, int16_t *txpow)
{
	int i;

	for (i = 0; i < nc; i++) {
		const struct ieee80211_channel *c = &chans[i];
		int type;

		if (showchannels)
			printf("%s%3d", sep,
			    ath_hal_mhz2ieee(ah, c->ic_freq, c->ic_flags));
		else
			printf("%s%u", sep, c->ic_freq);
		if (IEEE80211_IS_CHAN_HALF(c))
			type = 'H';
		else if (IEEE80211_IS_CHAN_QUARTER(c))
			type = 'Q';
		else if (IEEE80211_IS_CHAN_TURBO(c))
			type = 'T';
		else if (IEEE80211_IS_CHAN_HT(c))
			type = 'N';
		else if (IEEE80211_IS_CHAN_A(c))
			type = 'A';
		else if (IEEE80211_IS_CHAN_108G(c))
			type = 'T';
		else if (IEEE80211_IS_CHAN_G(c))
			type = 'G';
		else
			type = 'B';
		if (dopassive && IEEE80211_IS_CHAN_PASSIVE(c))
			type = tolower(type);
		if (isdfs && is4ms)
			printf("%c%c%c %d.%d", type,
			    IEEE80211_IS_CHAN_DFS(c) ? '*' : ' ',
			    IEEE80211_IS_CHAN_4MS(c) ? '4' : ' ',
			    txpow[i]/2, (txpow[i]%2)*5);
		else if (isdfs)
			printf("%c%c %d.%d", type,
			    IEEE80211_IS_CHAN_DFS(c) ? '*' : ' ',
			    txpow[i]/2, (txpow[i]%2)*5);
		else if (is4ms)
			printf("%c%c %d.%d", type,
			    IEEE80211_IS_CHAN_4MS(c) ? '4' : ' ',
			    txpow[i]/2, (txpow[i]%2)*5);
		else
			printf("%c %d.%d", type, txpow[i]/2, (txpow[i]%2)*5);
		if ((n++ % (showchannels ? 7 : 6)) == 0)
			sep = "\n";
		else
			sep = " ";
	}
}