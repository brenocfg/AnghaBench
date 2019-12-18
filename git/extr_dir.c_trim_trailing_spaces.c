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

__attribute__((used)) static void trim_trailing_spaces(char *buf)
{
	char *p, *last_space = NULL;

	for (p = buf; *p; p++)
		switch (*p) {
		case ' ':
			if (!last_space)
				last_space = p;
			break;
		case '\\':
			p++;
			if (!*p)
				return;
			/* fallthrough */
		default:
			last_space = NULL;
		}

	if (last_space)
		*last_space = '\0';
}