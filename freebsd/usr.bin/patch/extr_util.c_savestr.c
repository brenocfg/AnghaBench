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
 int /*<<< orphan*/  fatal (char*) ; 
 int out_of_mem ; 
 char* strdup (char const*) ; 
 scalar_t__ using_plan_a ; 

char *
savestr(const char *s)
{
	char	*rv;

	if (!s)
		s = "Oops";
	rv = strdup(s);
	if (rv == NULL) {
		if (using_plan_a)
			out_of_mem = true;
		else
			fatal("out of memory\n");
	}
	return rv;
}