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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t
devclass_equal(const char *a, const char *b)
{
	char ta, tb;

	if (a == b)
		return (1);

	while (1) {
		ta = *a;
		tb = *b;
		if (ta != tb)
			return (0);
		if (ta == 0)
			break;
		a++;
		b++;
	}
	return (1);
}