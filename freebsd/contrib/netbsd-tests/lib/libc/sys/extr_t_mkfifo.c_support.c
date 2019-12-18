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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ mkfifo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
support(void)
{

	errno = 0;

	if (mkfifo(path, 0600) == 0) {
		ATF_REQUIRE(unlink(path) == 0);
		return;
	}

	if (errno == EOPNOTSUPP)
		atf_tc_skip("the kernel does not support FIFOs");
	else {
		atf_tc_fail("mkfifo(2) failed");
	}
}