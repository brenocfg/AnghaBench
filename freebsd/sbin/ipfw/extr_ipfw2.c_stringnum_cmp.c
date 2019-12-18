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
 int strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 

int
stringnum_cmp(const char *a, const char *b)
{
	int la, lb;

	la = strlen(a);
	lb = strlen(b);

	if (la > lb)
		return (1);
	else if (la < lb)
		return (-01);

	return (strcmp(a, b));
}