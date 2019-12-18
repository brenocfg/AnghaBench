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
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 

int
_substrcmp2(const char *str1, const char* str2, const char* str3)
{

	if (strncmp(str1, str2, strlen(str2)) != 0)
		return 1;

	if (strcmp(str1, str3) != 0)
		warnx("DEPRECATED: '%s' matched '%s'",
		    str1, str3);
	return 0;
}