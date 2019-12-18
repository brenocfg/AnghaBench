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
typedef  int /*<<< orphan*/  oldvalue ;
typedef  int /*<<< orphan*/  newvalue ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENOTCAPABLE ; 
 int /*<<< orphan*/  SYSCTL0_NAME ; 
 unsigned int SYSCTL0_READ0 ; 
 unsigned int SYSCTL0_READ1 ; 
 unsigned int SYSCTL0_READ2 ; 
 unsigned int SYSCTL0_READ_WRITE ; 
 unsigned int SYSCTL0_WRITE ; 
 int /*<<< orphan*/  SYSCTL1_NAME ; 
 unsigned int SYSCTL1_READ0 ; 
 unsigned int SYSCTL1_READ1 ; 
 unsigned int SYSCTL1_READ2 ; 
 unsigned int SYSCTL1_READ_WRITE ; 
 unsigned int SYSCTL1_WRITE ; 
 int cap_sysctl (int /*<<< orphan*/ *,int*,size_t,int*,size_t*,int*,int) ; 
 scalar_t__ cap_sysctlbyname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,size_t*,int*,int) ; 
 size_t nitems (int*) ; 
 scalar_t__ sysctlnametomib (int /*<<< orphan*/ ,int*,size_t*) ; 

__attribute__((used)) static unsigned int
checkcaps(cap_channel_t *capsysctl)
{
	unsigned int result;
	size_t len0, len1, oldsize;
	int error, mib0[2], mib1[2], oldvalue, newvalue;

	result = 0;

	len0 = nitems(mib0);
	ATF_REQUIRE(sysctlnametomib(SYSCTL0_NAME, mib0, &len0) == 0);
	len1 = nitems(mib1);
	ATF_REQUIRE(sysctlnametomib(SYSCTL1_NAME, mib1, &len1) == 0);

	oldsize = sizeof(oldvalue);
	if (cap_sysctlbyname(capsysctl, SYSCTL0_NAME, &oldvalue, &oldsize,
	    NULL, 0) == 0) {
		if (oldsize == sizeof(oldvalue))
			result |= SYSCTL0_READ0;
	}
	error = cap_sysctl(capsysctl, mib0, len0, &oldvalue, &oldsize, NULL, 0);
	if ((result & SYSCTL0_READ0) != 0)
		ATF_REQUIRE(error == 0);
	else
		ATF_REQUIRE_ERRNO(ENOTCAPABLE, error != 0);

	newvalue = 123;
	if (cap_sysctlbyname(capsysctl, SYSCTL0_NAME, NULL, NULL, &newvalue,
	    sizeof(newvalue)) == 0) {
		result |= SYSCTL0_WRITE;
	}

	if ((result & SYSCTL0_WRITE) != 0) {
		oldsize = sizeof(oldvalue);
		if (cap_sysctlbyname(capsysctl, SYSCTL0_NAME, &oldvalue,
		    &oldsize, NULL, 0) == 0) {
			if (oldsize == sizeof(oldvalue) && oldvalue == 123)
				result |= SYSCTL0_READ1;
		}
	}
	newvalue = 123;
	error = cap_sysctl(capsysctl, mib0, len0, NULL, NULL,
	    &newvalue, sizeof(newvalue));
	if ((result & SYSCTL0_WRITE) != 0)
		ATF_REQUIRE(error == 0);
	else
		ATF_REQUIRE_ERRNO(ENOTCAPABLE, error != 0);

	oldsize = sizeof(oldvalue);
	newvalue = 4567;
	if (cap_sysctlbyname(capsysctl, SYSCTL0_NAME, &oldvalue, &oldsize,
	    &newvalue, sizeof(newvalue)) == 0) {
		if (oldsize == sizeof(oldvalue) && oldvalue == 123)
			result |= SYSCTL0_READ_WRITE;
	}

	if ((result & SYSCTL0_READ_WRITE) != 0) {
		oldsize = sizeof(oldvalue);
		if (cap_sysctlbyname(capsysctl, SYSCTL0_NAME, &oldvalue,
		    &oldsize, NULL, 0) == 0) {
			if (oldsize == sizeof(oldvalue) && oldvalue == 4567)
				result |= SYSCTL0_READ2;
		}
	}

	oldsize = sizeof(oldvalue);
	if (cap_sysctlbyname(capsysctl, SYSCTL1_NAME, &oldvalue, &oldsize,
	    NULL, 0) == 0) {
		if (oldsize == sizeof(oldvalue))
			result |= SYSCTL1_READ0;
	}
	error = cap_sysctl(capsysctl, mib1, len1, &oldvalue, &oldsize, NULL, 0);
	if ((result & SYSCTL1_READ0) != 0)
		ATF_REQUIRE(error == 0);
	else
		ATF_REQUIRE_ERRNO(ENOTCAPABLE, error != 0);

	newvalue = 506;
	if (cap_sysctlbyname(capsysctl, SYSCTL1_NAME, NULL, NULL, &newvalue,
	    sizeof(newvalue)) == 0) {
		result |= SYSCTL1_WRITE;
	}

	if ((result & SYSCTL1_WRITE) != 0) {
		newvalue = 506;
		ATF_REQUIRE(cap_sysctl(capsysctl, mib1, len1, NULL, NULL,
		    &newvalue, sizeof(newvalue)) == 0);

		oldsize = sizeof(oldvalue);
		if (cap_sysctlbyname(capsysctl, SYSCTL1_NAME, &oldvalue,
		    &oldsize, NULL, 0) == 0) {
			if (oldsize == sizeof(oldvalue) && oldvalue == 506)
				result |= SYSCTL1_READ1;
		}
	}
	newvalue = 506;
	error = cap_sysctl(capsysctl, mib1, len1, NULL, NULL,
	    &newvalue, sizeof(newvalue));
	if ((result & SYSCTL1_WRITE) != 0)
		ATF_REQUIRE(error == 0);
	else
		ATF_REQUIRE_ERRNO(ENOTCAPABLE, error != 0);

	oldsize = sizeof(oldvalue);
	newvalue = 7008;
	if (cap_sysctlbyname(capsysctl, SYSCTL1_NAME, &oldvalue, &oldsize,
	    &newvalue, sizeof(newvalue)) == 0) {
		if (oldsize == sizeof(oldvalue) && oldvalue == 506)
			result |= SYSCTL1_READ_WRITE;
	}

	if ((result & SYSCTL1_READ_WRITE) != 0) {
		oldsize = sizeof(oldvalue);
		if (cap_sysctlbyname(capsysctl, SYSCTL1_NAME, &oldvalue,
		    &oldsize, NULL, 0) == 0) {
			if (oldsize == sizeof(oldvalue) && oldvalue == 7008)
				result |= SYSCTL1_READ2;
		}
	}

	return (result);
}