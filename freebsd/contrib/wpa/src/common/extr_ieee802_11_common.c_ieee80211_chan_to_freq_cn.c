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

__attribute__((used)) static int ieee80211_chan_to_freq_cn(u8 op_class, u8 chan)
{
	switch (op_class) {
	case 7: /* channels 1..13 */
	case 8: /* channels 1..9; 40 MHz */
	case 9: /* channels 5..13; 40 MHz */
		if (chan < 1 || chan > 13)
			return -1;
		return 2407 + 5 * chan;
	case 1: /* channels 36,40,44,48 */
	case 2: /* channels 52,56,60,64; dfs */
	case 4: /* channels 36,44; 40 MHz */
	case 5: /* channels 52,60; 40 MHz */
		if (chan < 36 || chan > 64)
			return -1;
		return 5000 + 5 * chan;
	case 3: /* channels 149,153,157,161,165 */
	case 6: /* channels 149,157; 40 MHz */
		if (chan < 149 || chan > 165)
			return -1;
		return 5000 + 5 * chan;
	}
	return -1;
}