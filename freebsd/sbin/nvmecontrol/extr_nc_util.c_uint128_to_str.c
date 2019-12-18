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
typedef  int uint128_t ;

/* Variables and functions */

char *
uint128_to_str(uint128_t u, char *buf, size_t buflen)
{
	char *end = buf + buflen - 1;

	*end-- = '\0';
	if (u == 0)
		*end-- = '0';
	while (u && end >= buf) {
		*end-- = u % 10 + '0';
		u /= 10;
	}
	end++;
	if (u != 0)
		return NULL;

	return end;
}