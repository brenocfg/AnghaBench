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
 long INT_MAX ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 long strtol (char const*,char**,int) ; 

int
eatoi(const char *s)
{
	char *cp;
	long l;

	l = strtol(s, &cp, 10);
	if (l > INT_MAX || *cp != '\0')
		errx(1, "error converting to integer: %s", s);
	return ((int)l);
}