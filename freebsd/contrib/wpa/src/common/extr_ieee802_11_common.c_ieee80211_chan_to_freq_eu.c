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

__attribute__((used)) static int ieee80211_chan_to_freq_eu(u8 op_class, u8 chan)
{
	switch (op_class) {
	case 4: /* channels 1..13 */
	case 11: /* channels 1..9; 40 MHz */
	case 12: /* channels 5..13; 40 MHz */
		if (chan < 1 || chan > 13)
			return -1;
		return 2407 + 5 * chan;
	case 1: /* channels 36,40,44,48 */
	case 2: /* channels 52,56,60,64; dfs */
	case 5: /* channels 36,44; 40 MHz */
	case 6: /* channels 52,60; 40 MHz */
	case 8: /* channels 40,48; 40 MHz */
	case 9: /* channels 56,64; 40 MHz */
		if (chan < 36 || chan > 64)
			return -1;
		return 5000 + 5 * chan;
	case 3: /* channels 100-140 */
	case 7: /* channels 100-132; 40 MHz */
	case 10: /* channels 104-136; 40 MHz */
	case 16: /* channels 100-140 */
		if (chan < 100 || chan > 140)
			return -1;
		return 5000 + 5 * chan;
	case 17: /* channels 149,153,157,161,165,169 */
		if (chan < 149 || chan > 169)
			return -1;
		return 5000 + 5 * chan;
	case 18: /* 60 GHz band, channels 1..4 */
		if (chan < 1 || chan > 4)
			return -1;
		return 56160 + 2160 * chan;
	}
	return -1;
}