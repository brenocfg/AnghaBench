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
 int display_mode_esc_sequence_len (char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ utf8_width (char const**,int /*<<< orphan*/ *) ; 

int utf8_strnwidth(const char *string, int len, int skip_ansi)
{
	int width = 0;
	const char *orig = string;

	if (len == -1)
		len = strlen(string);
	while (string && string < orig + len) {
		int skip;
		while (skip_ansi &&
		       (skip = display_mode_esc_sequence_len(string)) != 0)
			string += skip;
		width += utf8_width(&string, NULL);
	}
	return string ? width : len;
}