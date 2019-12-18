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
typedef  int uint8_t ;
typedef  enum ieee80211_phytype { ____Placeholder_ieee80211_phytype } ieee80211_phytype ;

/* Variables and functions */
 int IEEE80211_T_CCK ; 
 int IEEE80211_T_OFDM ; 

uint8_t
ieee80211_plcp2rate(uint8_t plcp, enum ieee80211_phytype type)
{
	if (type == IEEE80211_T_OFDM) {
		static const uint8_t ofdm_plcp2rate[16] = {
			[0xb]	= 12,
			[0xf]	= 18,
			[0xa]	= 24,
			[0xe]	= 36,
			[0x9]	= 48,
			[0xd]	= 72,
			[0x8]	= 96,
			[0xc]	= 108
		};
		return ofdm_plcp2rate[plcp & 0xf];
	}
	if (type == IEEE80211_T_CCK) {
		static const uint8_t cck_plcp2rate[16] = {
			[0xa]	= 2,	/* 0x0a */
			[0x4]	= 4,	/* 0x14 */
			[0x7]	= 11,	/* 0x37 */
			[0xe]	= 22,	/* 0x6e */
			[0xc]	= 44,	/* 0xdc , actually PBCC */
		};
		return cck_plcp2rate[plcp & 0xf];
	}
	return 0;
}