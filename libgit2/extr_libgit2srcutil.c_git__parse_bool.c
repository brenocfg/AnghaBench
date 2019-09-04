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
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

int git__parse_bool(int *out, const char *value)
{
	/* A missing value means true */
	if (value == NULL ||
		!strcasecmp(value, "true") ||
		!strcasecmp(value, "yes") ||
		!strcasecmp(value, "on")) {
		*out = 1;
		return 0;
	}
	if (!strcasecmp(value, "false") ||
		!strcasecmp(value, "no") ||
		!strcasecmp(value, "off") ||
		value[0] == '\0') {
		*out = 0;
		return 0;
	}

	return -1;
}