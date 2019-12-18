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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int EINVAL ; 
 int errno ; 
 int expand_number (char const*,scalar_t__*) ; 

__attribute__((used)) static int
parse_uint64(uint64_t *valp, uint64_t min, uint64_t max, const char *arg)
{
	uint64_t val;

	if (expand_number(arg, &val) == -1)
		return (errno);
	if (val < min || val > max)
		return (EINVAL);
	*valp = val;
	return (0);
}