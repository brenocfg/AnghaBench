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
typedef  int uintmax_t ;
typedef  int intmax_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 int labs (int) ; 
 int /*<<< orphan*/  parse_unit_factor (char*,int*) ; 
 int strtoimax (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_parse_signed(const char *value, intmax_t *ret, intmax_t max)
{
	if (value && *value) {
		char *end;
		intmax_t val;
		uintmax_t uval;
		uintmax_t factor = 1;

		errno = 0;
		val = strtoimax(value, &end, 0);
		if (errno == ERANGE)
			return 0;
		if (!parse_unit_factor(end, &factor)) {
			errno = EINVAL;
			return 0;
		}
		uval = labs(val);
		uval *= factor;
		if (uval > max || labs(val) > uval) {
			errno = ERANGE;
			return 0;
		}
		val *= factor;
		*ret = val;
		return 1;
	}
	errno = EINVAL;
	return 0;
}