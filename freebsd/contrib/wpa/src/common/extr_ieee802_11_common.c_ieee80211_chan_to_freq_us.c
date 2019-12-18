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

__attribute__((used)) static int ieee80211_chan_to_freq_us(u8 op_class, u8 chan)
{
	switch (op_class) {
	case 12: /* channels 1..11 */
	case 32: /* channels 1..7; 40 MHz */
	case 33: /* channels 5..11; 40 MHz */
		if (chan < 1 || chan > 11)
			return -1;
		return 2407 + 5 * chan;
	case 1: /* channels 36,40,44,48 */
	case 2: /* channels 52,56,60,64; dfs */
	case 22: /* channels 36,44; 40 MHz */
	case 23: /* channels 52,60; 40 MHz */
	case 27: /* channels 40,48; 40 MHz */
	case 28: /* channels 56,64; 40 MHz */
		if (chan < 36 || chan > 64)
			return -1;
		return 5000 + 5 * chan;
	case 4: /* channels 100-144 */
	case 24: /* channels 100-140; 40 MHz */
		if (chan < 100 || chan > 144)
			return -1;
		return 5000 + 5 * chan;
	case 3: /* channels 149,153,157,161 */
	case 25: /* channels 149,157; 40 MHz */
	case 26: /* channels 149,157; 40 MHz */
	case 30: /* channels 153,161; 40 MHz */
	case 31: /* channels 153,161; 40 MHz */
		if (chan < 149 || chan > 161)
			return -1;
		return 5000 + 5 * chan;
	case 5: /* channels 149,153,157,161,165 */
		if (chan < 149 || chan > 165)
			return -1;
		return 5000 + 5 * chan;
	case 34: /* 60 GHz band, channels 1..3 */
		if (chan < 1 || chan > 3)
			return -1;
		return 56160 + 2160 * chan;
	}
	return -1;
}