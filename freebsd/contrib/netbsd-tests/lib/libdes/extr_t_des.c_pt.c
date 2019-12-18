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

__attribute__((used)) static char *
pt(unsigned char *p)
{
	static char bufs[10][20];
	static int bnum = 0;
	char *ret;
	int i;
	static const char *f = "0123456789ABCDEF";

	ret = &(bufs[bnum++][0]);
	bnum %= 10;
	for (i = 0; i < 8; i++) {
		ret[i * 2] = f[(p[i] >> 4) & 0xf];
		ret[i * 2 + 1] = f[p[i] & 0xf];
	}
	ret[16] = '\0';
	return (ret);
}