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

/* Variables and functions */

__attribute__((used)) static int
strtoi_lim(const char *str, const char **ep, int llim, int ulim)
{
	int res = 0;
	const char *sp;
	/* we keep track of the number of digits via rulim */
	int rulim;

	for (sp = str, rulim = ulim > 10 ? ulim : 10;
	     res * 10 <= ulim && rulim && *sp >= '0' && *sp <= '9';
	     sp++, rulim /= 10) {
		res *= 10;
		res += *sp - '0';
	}
	if (sp == str) {
		res = -1;
	} else if (res < llim || res > ulim) {
		res = -2;
	}
	*ep = (const char*)sp;
	return res;
}