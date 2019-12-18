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
 scalar_t__ isspace (char) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *clean_val(char *val)
{
	char *p = val;
	/* clean leading spaces */
	while (isspace(*p))
		p++;
	val = p;
	if (!*val)
		return val;
	/* clean trailing spaces */
	p = val + strlen(val) - 1;
	while (p > val && isspace(*p))
		p--;
	p[1] = '\0';
	/* clean quotas */
	if ((*val == '\"' && *p == '\"') || (*val == '\'' && *p == '\'')) {
		val++;
		*p-- = '\0';
	}
	return val;
}