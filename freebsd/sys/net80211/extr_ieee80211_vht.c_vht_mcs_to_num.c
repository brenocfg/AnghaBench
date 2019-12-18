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

/* Variables and functions */
#define  IEEE80211_VHT_MCS_SUPPORT_0_7 130 
#define  IEEE80211_VHT_MCS_SUPPORT_0_8 129 
#define  IEEE80211_VHT_MCS_SUPPORT_0_9 128 

__attribute__((used)) static int
vht_mcs_to_num(int m)
{

	switch (m) {
	case IEEE80211_VHT_MCS_SUPPORT_0_7:
		return (7);
	case IEEE80211_VHT_MCS_SUPPORT_0_8:
		return (8);
	case IEEE80211_VHT_MCS_SUPPORT_0_9:
		return (9);
	default:
		return (0);
	}
}