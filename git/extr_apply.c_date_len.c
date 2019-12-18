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
 scalar_t__ isdigit (char const) ; 
 int strlen (char*) ; 

__attribute__((used)) static size_t date_len(const char *line, size_t len)
{
	const char *date, *p;

	if (len < strlen("72-02-05") || line[len-strlen("-05")] != '-')
		return 0;
	p = date = line + len - strlen("72-02-05");

	if (!isdigit(*p++) || !isdigit(*p++) || *p++ != '-' ||
	    !isdigit(*p++) || !isdigit(*p++) || *p++ != '-' ||
	    !isdigit(*p++) || !isdigit(*p++))	/* Not a date. */
		return 0;

	if (date - line >= strlen("19") &&
	    isdigit(date[-1]) && isdigit(date[-2]))	/* 4-digit year */
		date -= strlen("19");

	return line + len - date;
}