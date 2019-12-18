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
typedef  int uint64_t ;

/* Variables and functions */

char *
conv_cnt_human_readable(uint64_t val64, float *val, int data)
{
	uint64_t tmp = val64;
	int ui = 0;
	int div = 1;

	tmp /= 1024;
	while (tmp) {
		ui++;
		tmp /= 1024;
		div *= 1024;
	}

	*val = (float)(val64);
	if (data) {
		*val *= 4;
		if (*val/div > 1024) {
			ui++;
			div *= 1024;
		}
	}
	*val /= div;

	if (data) {
		switch (ui) {
			case 0:
				return ("B");
			case 1:
				return ("KB");
			case 2:
				return ("MB");
			case 3:
				return ("GB");
			case 4:
				return ("TB");
			case 5:
				return ("PB");
			case 6:
				return ("EB");
			default:
				return ("");
		}
	} else {
		switch (ui) {
			case 0:
				return ("");
			case 1:
				return ("K");
			case 2:
				return ("M");
			case 3:
				return ("G");
			case 4:
				return ("T");
			case 5:
				return ("P");
			case 6:
				return ("E");
			default:
				return ("");
		}
	}
	return ("");
}