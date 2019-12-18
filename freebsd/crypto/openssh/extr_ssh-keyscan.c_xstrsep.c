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
 int strcspn (char*,char const*) ; 

__attribute__((used)) static char *
xstrsep(char **str, const char *delim)
{
	char *s, *e;

	if (!**str)
		return (NULL);

	s = *str;
	e = s + strcspn(s, delim);

	if (*e != '\0')
		*e++ = '\0';
	*str = e;

	return (s);
}