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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int IEEE80211_CHAN_B ; 
 int IEEE80211_CHAN_G ; 
 int IEEE80211_CHAN_HT20 ; 
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NG ; 
 scalar_t__ isset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getflags_2ghz(const uint8_t bands[], uint32_t flags[], int ht40)
{
	int nmodes;

	nmodes = 0;
	if (isset(bands, IEEE80211_MODE_11B))
		flags[nmodes++] = IEEE80211_CHAN_B;
	if (isset(bands, IEEE80211_MODE_11G))
		flags[nmodes++] = IEEE80211_CHAN_G;
	if (isset(bands, IEEE80211_MODE_11NG))
		flags[nmodes++] = IEEE80211_CHAN_G | IEEE80211_CHAN_HT20;
	if (ht40) {
		flags[nmodes++] = IEEE80211_CHAN_G | IEEE80211_CHAN_HT40U;
		flags[nmodes++] = IEEE80211_CHAN_G | IEEE80211_CHAN_HT40D;
	}
	flags[nmodes] = 0;
}