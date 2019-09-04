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
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static size_t tz_with_colon_len(const char *line, size_t len)
{
	const char *tz, *p;

	if (len < strlen(" +08:00") || line[len - strlen(":00")] != ':')
		return 0;
	tz = line + len - strlen(" +08:00");

	if (tz[0] != ' ' || (tz[1] != '+' && tz[1] != '-'))
		return 0;
	p = tz + 2;
	if (!isdigit(*p++) || !isdigit(*p++) || *p++ != ':' ||
	    !isdigit(*p++) || !isdigit(*p++))
		return 0;

	return line + len - tz;
}