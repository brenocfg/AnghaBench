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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void
tohex(char **buf, int len, uint32_t val)
{
	static const char *hexstr = "0123456789abcdef";
	char *walker = *buf;
	int i;

	for (i = len - 1; i >= 0; i--) {
		walker[i] = hexstr[val & 0xf];
		val >>= 4;
	}
	*buf = walker + len;
}