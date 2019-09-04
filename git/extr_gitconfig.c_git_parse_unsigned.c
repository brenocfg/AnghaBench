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
typedef  scalar_t__ uintmax_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  parse_unit_factor (char*,scalar_t__*) ; 
 scalar_t__ strtoumax (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_parse_unsigned(const char *value, uintmax_t *ret, uintmax_t max)
{
	if (value && *value) {
		char *end;
		uintmax_t val;
		uintmax_t oldval;

		errno = 0;
		val = strtoumax(value, &end, 0);
		if (errno == ERANGE)
			return 0;
		oldval = val;
		if (!parse_unit_factor(end, &val)) {
			errno = EINVAL;
			return 0;
		}
		if (val > max || oldval > val) {
			errno = ERANGE;
			return 0;
		}
		*ret = val;
		return 1;
	}
	errno = EINVAL;
	return 0;
}