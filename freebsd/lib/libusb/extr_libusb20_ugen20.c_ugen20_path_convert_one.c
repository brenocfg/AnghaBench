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

__attribute__((used)) static uint32_t
ugen20_path_convert_one(const char **pp)
{
	const char *ptr;
	uint32_t temp = 0;

	ptr = *pp;

	while ((*ptr >= '0') && (*ptr <= '9')) {
		temp *= 10;
		temp += (*ptr - '0');
		if (temp >= 1000000) {
			/* catch overflow early */
			return (0xFFFFFFFF);
		}
		ptr++;
	}

	if (*ptr == '.') {
		/* skip dot */
		ptr++;
	}
	*pp = ptr;

	return (temp);
}