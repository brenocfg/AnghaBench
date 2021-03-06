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
from_octal(const char *p, size_t l)
{
	int r = 0;

	while (l > 0) {
		r *= 8;
		r += *p - '0';
		--l;
		++p;
	}
	return (r);
}