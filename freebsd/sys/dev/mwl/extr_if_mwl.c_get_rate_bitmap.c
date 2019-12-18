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
typedef  int uint32_t ;
struct ieee80211_rateset {int rs_nrates; int* rs_rates; } ;

/* Variables and functions */
 int IEEE80211_RATE_VAL ; 

__attribute__((used)) static uint32_t
get_rate_bitmap(const struct ieee80211_rateset *rs)
{
	uint32_t rates;
	int i;

	rates = 0;
	for (i = 0; i < rs->rs_nrates; i++)
		switch (rs->rs_rates[i] & IEEE80211_RATE_VAL) {
		case 2:	  rates |= 0x001; break;
		case 4:	  rates |= 0x002; break;
		case 11:  rates |= 0x004; break;
		case 22:  rates |= 0x008; break;
		case 44:  rates |= 0x010; break;
		case 12:  rates |= 0x020; break;
		case 18:  rates |= 0x040; break;
		case 24:  rates |= 0x080; break;
		case 36:  rates |= 0x100; break;
		case 48:  rates |= 0x200; break;
		case 72:  rates |= 0x400; break;
		case 96:  rates |= 0x800; break;
		case 108: rates |= 0x1000; break;
		}
	return rates;
}