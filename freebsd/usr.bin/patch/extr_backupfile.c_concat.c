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
 int asprintf (char**,char*,char const*,char const*) ; 

__attribute__((used)) static char  *
concat(const char *str1, const char *str2)
{
	char	*newstr;

	if (asprintf(&newstr, "%s%s", str1, str2) == -1)
		return NULL;
	return newstr;
}