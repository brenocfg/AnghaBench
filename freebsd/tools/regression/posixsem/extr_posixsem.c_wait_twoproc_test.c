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
 int CSTAT_CLASS (int) ; 
 int /*<<< orphan*/  CSTAT_ERROR (int) ; 
 int /*<<< orphan*/  O_CREAT ; 
 int /*<<< orphan*/  TEST_PATH ; 
 int /*<<< orphan*/  check_alarm (int) ; 
 scalar_t__ child_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fail_err (char*,int) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int /*<<< orphan*/  ksem_close (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass () ; 
 scalar_t__ schedule_post (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_twoproc_child ; 

__attribute__((used)) static void
wait_twoproc_test(void)
{
	semid_t id;
	int stat;

	if (ksem_open(&id, TEST_PATH, O_CREAT, 0777, 0)) {
		fail_errno("ksem_open");
		return;
	}

	if (schedule_post(id, 500) < 0) {
		ksem_close(id);
		ksem_unlink(TEST_PATH);
		return;
	}		

	if (child_worker(wait_twoproc_child, NULL, &stat) < 0) {
		check_alarm(1);
		ksem_close(id);
		ksem_unlink(TEST_PATH);
		return;
	}

	errno = CSTAT_ERROR(stat);
	switch (CSTAT_CLASS(stat)) {
	case 0:
		pass();
		break;
	case 1:
		fail_errno("child ksem_open()");
		break;
	case 2:
		fail_errno("child ksem_wait()");
		break;
	case 3:
		fail_errno("child ksem_close()");
		break;
	default:
		fail_err("bad child state %#x", stat);
		break;
	}

	check_alarm(1);
	ksem_close(id);
	ksem_unlink(TEST_PATH);
}