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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAX_WIRED ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
vm_max_wired_sysctl(u_long *old_value, u_long *new_value)
{
	size_t old_len;
	size_t new_len = (new_value == NULL ? 0 : sizeof(*new_value));

	if (old_value == NULL)
		printf("Setting the new value to %lu\n", *new_value);
	else {
		ATF_REQUIRE_MSG(sysctlbyname(VM_MAX_WIRED, NULL, &old_len,
		    new_value, new_len) == 0,
		    "sysctlbyname(%s) failed: %s", VM_MAX_WIRED, strerror(errno));
	}

	ATF_REQUIRE_MSG(sysctlbyname(VM_MAX_WIRED, old_value, &old_len,
	    new_value, new_len) == 0,
	    "sysctlbyname(%s) failed: %s", VM_MAX_WIRED, strerror(errno));

	if (old_value != NULL)
		printf("Saved the old value (%lu)\n", *old_value);
}