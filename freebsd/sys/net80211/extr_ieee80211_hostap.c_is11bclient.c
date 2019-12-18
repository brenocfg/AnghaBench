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
typedef  int uint32_t ;

/* Variables and functions */
 int const IEEE80211_RATE_VAL ; 

__attribute__((used)) static int
is11bclient(const uint8_t *rates, const uint8_t *xrates)
{
	static const uint32_t brates = (1<<2*1)|(1<<2*2)|(1<<11)|(1<<2*11);
	int i;

	/* NB: the 11b clients we care about will not have xrates */
	if (xrates != NULL || rates == NULL)
		return 0;
	for (i = 0; i < rates[1]; i++) {
		int r = rates[2+i] & IEEE80211_RATE_VAL;
		if (r > 2*11 || ((1<<r) & brates) == 0)
			return 0;
	}
	return 1;
}