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
 struct ieee80211_channel const* IEEE80211_CHAN_ANYC ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel const*) ; 
 int IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_HT (struct ieee80211_channel const*) ; 
 int IEEE80211_IS_CHAN_HTA (struct ieee80211_channel const*) ; 
 int IEEE80211_IS_CHAN_HTG (struct ieee80211_channel const*) ; 
 int IEEE80211_IS_CHAN_STURBO (struct ieee80211_channel const*) ; 
#define  IEEE80211_MODE_11A 133 
#define  IEEE80211_MODE_11B 132 
#define  IEEE80211_MODE_11G 131 
#define  IEEE80211_MODE_11NA 130 
#define  IEEE80211_MODE_11NG 129 
#define  IEEE80211_MODE_STURBO_A 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static int
check_mode_consistency(const struct ieee80211_channel *c, int mode)
{
	KASSERT(c != IEEE80211_CHAN_ANYC, ("oops, no channel"));

	switch (mode) {
	case IEEE80211_MODE_11B:
		return (IEEE80211_IS_CHAN_B(c));
	case IEEE80211_MODE_11G:
		return (IEEE80211_IS_CHAN_ANYG(c) && !IEEE80211_IS_CHAN_HT(c));
	case IEEE80211_MODE_11A:
		return (IEEE80211_IS_CHAN_A(c) && !IEEE80211_IS_CHAN_HT(c));
	case IEEE80211_MODE_STURBO_A:
		return (IEEE80211_IS_CHAN_STURBO(c));
	case IEEE80211_MODE_11NA:
		return (IEEE80211_IS_CHAN_HTA(c));
	case IEEE80211_MODE_11NG:
		return (IEEE80211_IS_CHAN_HTG(c));
	}
	return 1;

}