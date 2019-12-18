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
struct ieee80211com {int ic_nchans; struct ieee80211_channel* ic_channels; } ;
struct ieee80211_channel {int ic_ieee; int ic_freq; int ic_maxregpower; int ic_minpower; int ic_maxpower; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_108A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40D (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40U (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_ST (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ieee80211_announce_channels(struct ieee80211com *ic)
{
	const struct ieee80211_channel *c;
	char type;
	int i, cw;

	printf("Chan  Freq  CW  RegPwr  MinPwr  MaxPwr\n");
	for (i = 0; i < ic->ic_nchans; i++) {
		c = &ic->ic_channels[i];
		if (IEEE80211_IS_CHAN_ST(c))
			type = 'S';
		else if (IEEE80211_IS_CHAN_108A(c))
			type = 'T';
		else if (IEEE80211_IS_CHAN_108G(c))
			type = 'G';
		else if (IEEE80211_IS_CHAN_HT(c))
			type = 'n';
		else if (IEEE80211_IS_CHAN_A(c))
			type = 'a';
		else if (IEEE80211_IS_CHAN_ANYG(c))
			type = 'g';
		else if (IEEE80211_IS_CHAN_B(c))
			type = 'b';
		else
			type = 'f';
		if (IEEE80211_IS_CHAN_HT40(c) || IEEE80211_IS_CHAN_TURBO(c))
			cw = 40;
		else if (IEEE80211_IS_CHAN_HALF(c))
			cw = 10;
		else if (IEEE80211_IS_CHAN_QUARTER(c))
			cw = 5;
		else
			cw = 20;
		printf("%4d  %4d%c %2d%c %6d  %4d.%d  %4d.%d\n"
			, c->ic_ieee, c->ic_freq, type
			, cw
			, IEEE80211_IS_CHAN_HT40U(c) ? '+' :
			  IEEE80211_IS_CHAN_HT40D(c) ? '-' : ' '
			, c->ic_maxregpower
			, c->ic_minpower / 2, c->ic_minpower & 1 ? 5 : 0
			, c->ic_maxpower / 2, c->ic_maxpower & 1 ? 5 : 0
		);
	}
}