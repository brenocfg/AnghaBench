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

void *
memmove(void *dp, const void *sp, size_t n)
{
	unsigned char *cdp, *csp;

	if (n<=0)
		return dp;
	cdp = dp;
	csp = (unsigned char *)sp;
	if (cdp < csp) {
		do {
			*cdp++ = *csp++;
		} while (--n);
	} else {
		cdp += n;
		csp += n;
		do {
			*--cdp = *--csp;
		} while (--n);
	}
	return dp;
}