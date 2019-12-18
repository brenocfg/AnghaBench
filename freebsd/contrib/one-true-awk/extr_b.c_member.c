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
typedef  scalar_t__ uschar ;

/* Variables and functions */

int member(int c, const char *sarg)	/* is c in s? */
{
	uschar *s = (uschar *) sarg;

	while (*s)
		if (c == *s++)
			return(1);
	return(0);
}