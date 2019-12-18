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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 long strtol (char const*,char**,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timespec_arg(const char *arg, long int *set_time, int *set_eq)
{
	char *test;
	const char *timespec = arg;
	*set_eq = (*timespec == '=') ? 1 : 0;
	if (*set_eq) {
		timespec++;
		if (*timespec == '+') {
			*set_eq = 2; /* relative "in the future" */
			timespec++;
		}
	}
	*set_time = strtol(timespec, &test, 10);
	if (*test) {
		return 0;
	}
	if ((*set_eq && *set_time < 0) || *set_eq == 2) {
		time_t now = time(NULL);
		*set_time += now;
	}
	return 1;
}