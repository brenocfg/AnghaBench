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

unsigned char *
i2octets(int n, size_t i)
{
	static unsigned char o[16];
	int x, j;

	if (n > 15)
		return (NULL);
	for (j = 0, x = n - 1; x >= 0; x--, j++) {
		o[j] = (unsigned char)((i & (0xff << x * 8)) >> x * 8);
	}
	return (o);
}