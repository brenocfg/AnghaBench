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
 char* ambiguous ; 
 int isprefix (char*,char*) ; 

char **
genget(char *name, char **table, int stlen)
{
	char **c, **found;
	int n;

	if (name == 0)
	    return 0;

	found = 0;
	for (c = table; *c != 0; c = (char **)((char *)c + stlen)) {
		if ((n = isprefix(name, *c)) == 0)
			continue;
		if (n < 0)		/* exact match */
			return(c);
		if (found)
			return(&ambiguous);
		found = c;
	}
	return(found);
}