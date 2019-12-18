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
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fail_err (char*) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ ksem_getvalue (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pass () ; 

__attribute__((used)) static void
getvalue_invalid_semaphore(void)
{
	int val;

	if (ksem_getvalue(STDERR_FILENO, &val) >= 0) {
		fail_err("ksem_getvalue() didn't fail");
		return;
	}
	if (errno != EINVAL) {
		fail_errno("ksem_getvalue");
		return;
	}
	pass();
}