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
 int /*<<< orphan*/  isdigit (char const) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static size_t sane_tz_len(const char *line, size_t len)
{
	const char *tz, *p;

	if (len < strlen(" +0500") || line[len-strlen(" +0500")] != ' ')
		return 0;
	tz = line + len - strlen(" +0500");

	if (tz[1] != '+' && tz[1] != '-')
		return 0;

	for (p = tz + 2; p != line + len; p++)
		if (!isdigit(*p))
			return 0;

	return line + len - tz;
}