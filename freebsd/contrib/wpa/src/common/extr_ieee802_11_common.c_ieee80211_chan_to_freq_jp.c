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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static int ieee80211_chan_to_freq_jp(u8 op_class, u8 chan)
{
	switch (op_class) {
	case 30: /* channels 1..13 */
	case 56: /* channels 1..9; 40 MHz */
	case 57: /* channels 5..13; 40 MHz */
		if (chan < 1 || chan > 13)
			return -1;
		return 2407 + 5 * chan;
	case 31: /* channel 14 */
		if (chan != 14)
			return -1;
		return 2414 + 5 * chan;
	case 1: /* channels 34,38,42,46(old) or 36,40,44,48 */
	case 32: /* channels 52,56,60,64 */
	case 33: /* channels 52,56,60,64 */
	case 36: /* channels 36,44; 40 MHz */
	case 37: /* channels 52,60; 40 MHz */
	case 38: /* channels 52,60; 40 MHz */
	case 41: /* channels 40,48; 40 MHz */
	case 42: /* channels 56,64; 40 MHz */
	case 43: /* channels 56,64; 40 MHz */
		if (chan < 34 || chan > 64)
			return -1;
		return 5000 + 5 * chan;
	case 34: /* channels 100-140 */
	case 35: /* channels 100-140 */
	case 39: /* channels 100-132; 40 MHz */
	case 40: /* channels 100-132; 40 MHz */
	case 44: /* channels 104-136; 40 MHz */
	case 45: /* channels 104-136; 40 MHz */
	case 58: /* channels 100-140 */
		if (chan < 100 || chan > 140)
			return -1;
		return 5000 + 5 * chan;
	case 59: /* 60 GHz band, channels 1..4 */
		if (chan < 1 || chan > 3)
			return -1;
		return 56160 + 2160 * chan;
	}
	return -1;
}