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
typedef  int /*<<< orphan*/  int_value ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int,size_t,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctlbyname (char const*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_int_via_sysctlbyname(const char *oidname)
{
	size_t oldlen;
	int int_value;

	oldlen = sizeof(int_value);

	ATF_REQUIRE_EQ_MSG(sysctlbyname(oidname, &int_value, &oldlen, NULL, 0),
	    0, "sysctlbyname(%s, ...) failed: %s", oidname, strerror(errno));
	ATF_REQUIRE_EQ_MSG(sizeof(int_value), oldlen, "sanity check failed");

	return (int_value);
}