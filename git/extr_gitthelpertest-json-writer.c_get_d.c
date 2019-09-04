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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  die (char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  get_s (int,char**) ; 
 double strtod (char*,char**) ; 

__attribute__((used)) static void get_d(int line_nr, double *s_in)
{
	char *s;
	char *endptr;

	get_s(line_nr, &s);

	*s_in = strtod(s, &endptr);
	if (*endptr || errno == ERANGE)
		die("line[%d]: invalid float value", line_nr);
}