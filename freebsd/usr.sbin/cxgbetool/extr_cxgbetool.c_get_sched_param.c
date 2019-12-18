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
 int EINVAL ; 
 char* str_to_number (char const*,long*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 

__attribute__((used)) static int
get_sched_param(const char *param, const char *args[], long *val)
{
	char *p;

	if (strcmp(param, args[0]) != 0)
		return (EINVAL);

	p = str_to_number(args[1], val, NULL);
	if (*p) {
		warnx("parameter \"%s\" has bad value \"%s\"", args[0],
		    args[1]);
		return (EINVAL);
	}

	return (0);
}