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
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static const char *
find_pattern(char *line, const char *pattern)
{
	char *ptr;

	ptr = strsep(&line, " ");
	while (ptr != NULL) {
		if (!strcmp(ptr, pattern)) {
			/* Return the next. */
			ptr = strsep(&line, " ");
			return (ptr);
		}
		ptr = strsep(&line, " ");
	}
	return (NULL);
}