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
struct ieee80211_htrateset {int rs_nrates; int* rs_rates; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
get_htrate_bitmap(const struct ieee80211_htrateset *rs)
{
	uint32_t rates;
	int i;

	rates = 0;
	for (i = 0; i < rs->rs_nrates; i++) {
		if (rs->rs_rates[i] < 16)
			rates |= 1<<rs->rs_rates[i];
	}
	return rates;
}