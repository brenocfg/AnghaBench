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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  cn_op_class_cc ; 
 scalar_t__ country_match (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  eu_op_class_cc ; 
 int ieee80211_chan_to_freq_cn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_chan_to_freq_eu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_chan_to_freq_global (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_chan_to_freq_jp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_chan_to_freq_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jp_op_class_cc ; 
 int /*<<< orphan*/  us_op_class_cc ; 

int ieee80211_chan_to_freq(const char *country, u8 op_class, u8 chan)
{
	int freq;

	if (country_match(us_op_class_cc, country)) {
		freq = ieee80211_chan_to_freq_us(op_class, chan);
		if (freq > 0)
			return freq;
	}

	if (country_match(eu_op_class_cc, country)) {
		freq = ieee80211_chan_to_freq_eu(op_class, chan);
		if (freq > 0)
			return freq;
	}

	if (country_match(jp_op_class_cc, country)) {
		freq = ieee80211_chan_to_freq_jp(op_class, chan);
		if (freq > 0)
			return freq;
	}

	if (country_match(cn_op_class_cc, country)) {
		freq = ieee80211_chan_to_freq_cn(op_class, chan);
		if (freq > 0)
			return freq;
	}

	return ieee80211_chan_to_freq_global(op_class, chan);
}