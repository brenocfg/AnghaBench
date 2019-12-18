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
typedef  int ptrdiff_t ;

/* Variables and functions */
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
lookup(const char *str, const char *list)
{
	const char *next;
	size_t len;

	len = strlen(str);
	while (*list != '\0') {
		while (*list == ',')
			++list;
		if ((next = strchr(list, ',')) == NULL)
			next = strchr(list, '\0');
		if (next - list == (ptrdiff_t)len &&
		    strncmp(list, str, len) == 0)
			return (1);
		list = next;
	}
	return (0);
}