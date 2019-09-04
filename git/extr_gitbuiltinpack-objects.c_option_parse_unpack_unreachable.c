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
struct option {int dummy; } ;

/* Variables and functions */
 scalar_t__ approxidate (char const*) ; 
 int unpack_unreachable ; 
 scalar_t__ unpack_unreachable_expiration ; 

__attribute__((used)) static int option_parse_unpack_unreachable(const struct option *opt,
					   const char *arg, int unset)
{
	if (unset) {
		unpack_unreachable = 0;
		unpack_unreachable_expiration = 0;
	}
	else {
		unpack_unreachable = 1;
		if (arg)
			unpack_unreachable_expiration = approxidate(arg);
	}
	return 0;
}