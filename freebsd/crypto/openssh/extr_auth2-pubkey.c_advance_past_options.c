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
advance_past_options(char **cpp)
{
	char *cp = *cpp;
	int quoted = 0;

	for (; *cp && (quoted || (*cp != ' ' && *cp != '\t')); cp++) {
		if (*cp == '\\' && cp[1] == '"')
			cp++;	/* Skip both */
		else if (*cp == '"')
			quoted = !quoted;
	}
	*cpp = cp;
	/* return failure for unterminated quotes */
	return (*cp == '\0' && quoted) ? -1 : 0;
}