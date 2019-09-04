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

__attribute__((used)) static size_t short_time_len(const char *line, size_t len)
{
	const char *time, *p;

	if (len < strlen(" 07:01:32") || line[len-strlen(":32")] != ':')
		return 0;
	p = time = line + len - strlen(" 07:01:32");

	/* Permit 1-digit hours? */
	if (*p++ != ' ' ||
	    !isdigit(*p++) || !isdigit(*p++) || *p++ != ':' ||
	    !isdigit(*p++) || !isdigit(*p++) || *p++ != ':' ||
	    !isdigit(*p++) || !isdigit(*p++))	/* Not a time. */
		return 0;

	return line + len - time;
}