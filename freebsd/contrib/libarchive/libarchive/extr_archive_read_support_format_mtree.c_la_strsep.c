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
la_strsep(char **sp, const char *sep)
{
	char *p, *s;
	if (sp == NULL || *sp == NULL || **sp == '\0')
		return(NULL);
	s = *sp;
	p = s + strcspn(s, sep);
	if (*p != '\0')
		*p++ = '\0';
	*sp = p;
	return(s);
}