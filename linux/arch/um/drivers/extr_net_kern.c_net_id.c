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
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_id(char **str, int *start_out, int *end_out)
{
	char *end;
	int n;

	n = simple_strtoul(*str, &end, 0);
	if ((*end != '\0') || (end == *str))
		return -1;

	*start_out = n;
	*end_out = n;
	*str = end;
	return n;
}