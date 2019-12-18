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
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,size_t,char const*) ; 

__attribute__((used)) static char *
getstring(const char *fname, size_t line, char **cp, const char *tag)
{
	char *str;

	while ((str = strsep(cp, " \t")) != NULL && *str == '\0')
		continue;

	if (str == NULL)
		warnx("%s, %zu: no %s found", fname, line, tag);

	return str;
}