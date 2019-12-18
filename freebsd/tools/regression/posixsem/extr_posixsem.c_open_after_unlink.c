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
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TEST_PATH ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int /*<<< orphan*/  ksem_close (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ksem_open_should_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_after_unlink(void)
{
	semid_t id;

	if (ksem_open(&id, TEST_PATH, O_CREAT, 0777, 1) < 0) {
		fail_errno("ksem_open(1)");
		return;
	}
	ksem_close(id);

	if (ksem_unlink(TEST_PATH) < 0) {
		fail_errno("ksem_unlink");
		return;
	}

	ksem_open_should_fail(TEST_PATH, O_RDONLY, 0777, 1, ENOENT);
}