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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  errno ; 
 int expand_number (char const*,scalar_t__*) ; 

__attribute__((used)) static int
expand_number_int(const char *buf, int *num)
{
	int64_t num64;
	int rval;

	rval = expand_number(buf, &num64);
	if (rval < 0)
		return (rval);
	if (num64 > INT_MAX || num64 < INT_MIN) {
		errno = ERANGE;
		return (-1);
	}
	*num = (int)num64;
	return (0);
}