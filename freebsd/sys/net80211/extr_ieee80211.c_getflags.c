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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NA ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NG ; 
 int /*<<< orphan*/  IEEE80211_MODE_VHT_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_MODE_VHT_5GHZ ; 
 int /*<<< orphan*/  getflags_2ghz (int /*<<< orphan*/  const*,scalar_t__*,int) ; 
 int /*<<< orphan*/  getflags_5ghz (int /*<<< orphan*/  const*,scalar_t__*,int,int) ; 
 scalar_t__ isset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getflags(const uint8_t bands[], uint32_t flags[], int ht40, int vht80)
{

	flags[0] = 0;
	if (isset(bands, IEEE80211_MODE_11A) ||
	    isset(bands, IEEE80211_MODE_11NA) ||
	    isset(bands, IEEE80211_MODE_VHT_5GHZ)) {
		if (isset(bands, IEEE80211_MODE_11B) ||
		    isset(bands, IEEE80211_MODE_11G) ||
		    isset(bands, IEEE80211_MODE_11NG) ||
		    isset(bands, IEEE80211_MODE_VHT_2GHZ))
			return;

		getflags_5ghz(bands, flags, ht40, vht80);
	} else
		getflags_2ghz(bands, flags, ht40);
}