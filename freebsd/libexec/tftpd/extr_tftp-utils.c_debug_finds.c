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
 scalar_t__ debug_find (char*) ; 
 char* strchr (char*,char) ; 

int
debug_finds(char *s)
{
	int i = 0;
	char *ps = s;

	while (s != NULL) {
		ps = strchr(s, ' ');
		if (ps != NULL)
			*ps = '\0';
		i += debug_find(s);
		if (ps != NULL)
			*ps = ' ';
		s = ps;
	}
	return (i);
}