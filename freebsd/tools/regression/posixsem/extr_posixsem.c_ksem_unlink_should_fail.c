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
 int errno ; 
 int /*<<< orphan*/  fail_err (char*) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ ksem_unlink (char const*) ; 
 int /*<<< orphan*/  pass () ; 

__attribute__((used)) static void
ksem_unlink_should_fail(const char *path, int error)
{

	if (ksem_unlink(path) >= 0) {
		fail_err("ksem_unlink() didn't fail");
		return;
	}
	if (errno != error) {
		fail_errno("ksem_unlink");
		return;
	}
	pass();
}