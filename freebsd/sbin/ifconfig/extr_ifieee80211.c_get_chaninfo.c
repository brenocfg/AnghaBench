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
 scalar_t__ IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_FHSS (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT20 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40D (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40U (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT20 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT40D (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT40U (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT80 (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static const char *
get_chaninfo(const struct ieee80211_channel *c, int precise,
	char buf[], size_t bsize)
{
	buf[0] = '\0';
	if (IEEE80211_IS_CHAN_FHSS(c))
		strlcat(buf, " FHSS", bsize);
	if (IEEE80211_IS_CHAN_A(c))
		strlcat(buf, " 11a", bsize);
	else if (IEEE80211_IS_CHAN_ANYG(c))
		strlcat(buf, " 11g", bsize);
	else if (IEEE80211_IS_CHAN_B(c))
		strlcat(buf, " 11b", bsize);
	if (IEEE80211_IS_CHAN_HALF(c))
		strlcat(buf, "/10MHz", bsize);
	if (IEEE80211_IS_CHAN_QUARTER(c))
		strlcat(buf, "/5MHz", bsize);
	if (IEEE80211_IS_CHAN_TURBO(c))
		strlcat(buf, " Turbo", bsize);
	if (precise) {
		/* XXX should make VHT80U, VHT80D */
		if (IEEE80211_IS_CHAN_VHT80(c) &&
		    IEEE80211_IS_CHAN_HT40D(c))
			strlcat(buf, " vht/80-", bsize);
		else if (IEEE80211_IS_CHAN_VHT80(c) &&
		    IEEE80211_IS_CHAN_HT40U(c))
			strlcat(buf, " vht/80+", bsize);
		else if (IEEE80211_IS_CHAN_VHT80(c))
			strlcat(buf, " vht/80", bsize);
		else if (IEEE80211_IS_CHAN_VHT40D(c))
			strlcat(buf, " vht/40-", bsize);
		else if (IEEE80211_IS_CHAN_VHT40U(c))
			strlcat(buf, " vht/40+", bsize);
		else if (IEEE80211_IS_CHAN_VHT20(c))
			strlcat(buf, " vht/20", bsize);
		else if (IEEE80211_IS_CHAN_HT20(c))
			strlcat(buf, " ht/20", bsize);
		else if (IEEE80211_IS_CHAN_HT40D(c))
			strlcat(buf, " ht/40-", bsize);
		else if (IEEE80211_IS_CHAN_HT40U(c))
			strlcat(buf, " ht/40+", bsize);
	} else {
		if (IEEE80211_IS_CHAN_VHT(c))
			strlcat(buf, " vht", bsize);
		else if (IEEE80211_IS_CHAN_HT(c))
			strlcat(buf, " ht", bsize);
	}
	return buf;
}