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
 int MAXDEWEY ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int strtol (char*,char**,int) ; 

int
getdewey(int dewey[], char *cp)
{
	int	i, n;

	for (n = 0, i = 0; i < MAXDEWEY; i++) {
		if (*cp == '\0')
			break;

		if (*cp == '.') cp++;
		if (!isdigit(*cp))
			return 0;

		dewey[n++] = strtol(cp, &cp, 10);
	}

	return n;
}