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
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (scalar_t__,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  MODCTL_EXISTS ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 int modctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_permission(void)
{
	int err;

	err = modctl(MODCTL_EXISTS, 0);
	if (err == 0) return;
	if (errno == ENOSYS)
		atf_tc_skip("Kernel does not have 'options MODULAR'.");
	else if (errno == EPERM)
		atf_tc_skip("Module loading administratively forbidden");
	ATF_REQUIRE_EQ_MSG(errno, 0, "unexpected error %d from "
	    "modctl(MODCTL_EXISTS, 0)", errno);
}