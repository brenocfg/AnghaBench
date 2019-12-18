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

__attribute__((used)) static unsigned int
toi(const void *p, int n)
{
	const unsigned char *v = (const unsigned char *)p;
	if (n > 1)
		return v[0] + 256 * toi(v + 1, n - 1);
	if (n == 1)
		return v[0];
	return (0);
}