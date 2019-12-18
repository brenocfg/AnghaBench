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

__attribute__((used)) static bool last_line(size_t *out, const char *buf, size_t len)
{
	size_t i;

	*out = 0;

	if (len == 0)
		return false;
	if (len == 1)
		return true;

	/*
	 * Skip the last character (in addition to the null terminator),
	 * because if the last character is a newline, it is considered as part
	 * of the last line anyway.
	 */
	i = len - 2;

	for (; i > 0; i--) {
		if (buf[i] == '\n') {
			*out = i + 1;
			return true;
		}
	}
	return true;
}