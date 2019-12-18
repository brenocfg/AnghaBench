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

__attribute__((used)) static void no_mischief_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) {
		unsigned char s = src[i];
		int is_lower = s >= 'a' && s <= 'z';
		int is_upper = s >= 'A' && s <= 'Z';
		int is_digit = s >= '0' && s <= '9';

		if (is_lower || is_upper || is_digit) {
			/* TODO: if any manufacturer uses Unicode within the
			 * WPS header, it will get mangled here. */
			dst[i] = s;
		} else {
			/* Note that even spaces will be transformed to
			 * underscores, so 'Nexus 7' will turn into 'Nexus_7'.
			 * This is deliberate, to make the string easier to
			 * parse. */
			dst[i] = '_';
		}
	}
}