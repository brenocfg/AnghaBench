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

__attribute__((used)) static const char *quotes_for_value(const char *value)
{
	const char *ptr;

	if (value[0] == ' ' || value[0] == '\0')
		return "\"";

	for (ptr = value; *ptr; ++ptr) {
		if (*ptr == ';' || *ptr == '#')
			return "\"";
	}

	if (ptr[-1] == ' ')
		return "\"";

	return "";
}