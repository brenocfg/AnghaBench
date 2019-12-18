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
typedef  int /*<<< orphan*/  semid_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  TEST_PATH ; 
 scalar_t__ checkvalue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ ksem_close (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ ksem_post (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass () ; 

__attribute__((used)) static void
use_after_unlink_test(void)
{
	semid_t id;

	/*
	 * Create named semaphore with value of 1 and then unlink it
	 * while still retaining the initial reference.
	 */
	if (ksem_open(&id, TEST_PATH, O_CREAT | O_EXCL, 0777, 1) < 0) {
		fail_errno("ksem_open(O_CREAT | O_EXCL)");
		return;
	}
	if (ksem_unlink(TEST_PATH) < 0) {
		fail_errno("ksem_unlink");
		ksem_close(id);
		return;
	}
	if (checkvalue(id, 1) < 0) {
		ksem_close(id);
		return;
	}

	/* Post the semaphore to set its value to 2. */
	if (ksem_post(id) < 0) {
		fail_errno("ksem_post");
		ksem_close(id);
		return;
	}
	if (checkvalue(id, 2) < 0) {
		ksem_close(id);
		return;
	}

	/* Wait on the semaphore which should set its value to 1. */
	if (ksem_wait(id) < 0) {
		fail_errno("ksem_wait");
		ksem_close(id);
		return;
	}
	if (checkvalue(id, 1) < 0) {
		ksem_close(id);
		return;
	}

	if (ksem_close(id) < 0) {
		fail_errno("ksem_close");
		return;
	}
	pass();
}