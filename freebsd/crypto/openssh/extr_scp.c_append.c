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
 char** reallocarray (char**,size_t,int) ; 

__attribute__((used)) static int
append(char *cp, char ***ap, size_t *np)
{
	char **tmp;

	if ((tmp = reallocarray(*ap, *np + 1, sizeof(*tmp))) == NULL)
		return -1;
	tmp[(*np)] = cp;
	(*np)++;
	*ap = tmp;
	return 0;
}