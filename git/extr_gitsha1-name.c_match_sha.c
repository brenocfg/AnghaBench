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

__attribute__((used)) static int match_sha(unsigned len, const unsigned char *a, const unsigned char *b)
{
	do {
		if (*a != *b)
			return 0;
		a++;
		b++;
		len -= 2;
	} while (len > 1);
	if (len)
		if ((*a ^ *b) & 0xf0)
			return 0;
	return 1;
}