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
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static int section_name_match (const char *buf, const char *name)
{
	int i = 0, j = 0, dot = 0;
	if (buf[i] != '[')
		return 0;
	for (i = 1; buf[i] && buf[i] != ']'; i++) {
		if (!dot && isspace(buf[i])) {
			dot = 1;
			if (name[j++] != '.')
				break;
			for (i++; isspace(buf[i]); i++)
				; /* do nothing */
			if (buf[i] != '"')
				break;
			continue;
		}
		if (buf[i] == '\\' && dot)
			i++;
		else if (buf[i] == '"' && dot) {
			for (i++; isspace(buf[i]); i++)
				; /* do_nothing */
			break;
		}
		if (buf[i] != name[j++])
			break;
	}
	if (buf[i] == ']' && name[j] == 0) {
		/*
		 * We match, now just find the right length offset by
		 * gobbling up any whitespace after it, as well
		 */
		i++;
		for (; buf[i] && isspace(buf[i]); i++)
			; /* do nothing */
		return i;
	}
	return 0;
}