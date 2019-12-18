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
 int /*<<< orphan*/  git__isspace (char) ; 

__attribute__((used)) static size_t unescape_spaces(char *str)
{
	char *scan, *pos = str;
	bool escaped = false;

	if (!str)
		return 0;

	for (scan = str; *scan; scan++) {
		if (!escaped && *scan == '\\') {
			escaped = true;
			continue;
		}

		/* Only insert the escape character for escaped non-spaces */
		if (escaped && !git__isspace(*scan))
			*pos++ = '\\';

		*pos++ = *scan;
		escaped = false;
	}

	if (pos != scan)
		*pos = '\0';

	return (pos - str);
}