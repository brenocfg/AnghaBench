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
 int /*<<< orphan*/  in_delim (char,char const*) ; 

char *strsep(char **stringp, const char *delim)
{
	char* s;
	char* orig;
	if(stringp == NULL || *stringp == NULL)
		return NULL;
	orig = *stringp;
	s = *stringp;
	while(*s && !in_delim(*s, delim))
		s++;
	if(*s) {
		*s = 0;
		*stringp = s+1;
	} else {
		*stringp = NULL;
	}
	return orig;
}