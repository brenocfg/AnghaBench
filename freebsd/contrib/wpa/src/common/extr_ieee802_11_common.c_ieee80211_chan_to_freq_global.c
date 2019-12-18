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

__attribute__((used)) static int ieee80211_chan_to_freq_global(u8 op_class, u8 chan)
{
	/* Table E-4 in IEEE Std 802.11-2012 - Global operating classes */
	switch (op_class) {
	case 81:
		/* channels 1..13 */
		if (chan < 1 || chan > 13)
			return -1;
		return 2407 + 5 * chan;
	case 82:
		/* channel 14 */
		if (chan != 14)
			return -1;
		return 2414 + 5 * chan;
	case 83: /* channels 1..9; 40 MHz */
	case 84: /* channels 5..13; 40 MHz */
		if (chan < 1 || chan > 13)
			return -1;
		return 2407 + 5 * chan;
	case 115: /* channels 36,40,44,48; indoor only */
	case 116: /* channels 36,44; 40 MHz; indoor only */
	case 117: /* channels 40,48; 40 MHz; indoor only */
	case 118: /* channels 52,56,60,64; dfs */
	case 119: /* channels 52,60; 40 MHz; dfs */
	case 120: /* channels 56,64; 40 MHz; dfs */
		if (chan < 36 || chan > 64)
			return -1;
		return 5000 + 5 * chan;
	case 121: /* channels 100-140 */
	case 122: /* channels 100-142; 40 MHz */
	case 123: /* channels 104-136; 40 MHz */
		if (chan < 100 || chan > 140)
			return -1;
		return 5000 + 5 * chan;
	case 124: /* channels 149,153,157,161 */
	case 126: /* channels 149,157; 40 MHz */
	case 127: /* channels 153,161; 40 MHz */
		if (chan < 149 || chan > 161)
			return -1;
		return 5000 + 5 * chan;
	case 125: /* channels 149,153,157,161,165,169 */
		if (chan < 149 || chan > 169)
			return -1;
		return 5000 + 5 * chan;
	case 128: /* center freqs 42, 58, 106, 122, 138, 155; 80 MHz */
	case 130: /* center freqs 42, 58, 106, 122, 138, 155; 80 MHz */
		if (chan < 36 || chan > 161)
			return -1;
		return 5000 + 5 * chan;
	case 129: /* center freqs 50, 114; 160 MHz */
		if (chan < 36 || chan > 128)
			return -1;
		return 5000 + 5 * chan;
	case 180: /* 60 GHz band, channels 1..4 */
		if (chan < 1 || chan > 4)
			return -1;
		return 56160 + 2160 * chan;
	}
	return -1;
}