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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  semid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELAPSED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 scalar_t__ checkvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ ksem_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass () ; 
 scalar_t__ timedwait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expired_timedwait(void)
{
	semid_t id;
	u_int elapsed;

	if (ksem_init(&id, 0) < 0) {
		fail_errno("ksem_init");
		return;
	}

	/* This should fail with a timeout and leave the value at 0. */
	if (timedwait(id, 2500, &elapsed, ETIMEDOUT) < 0) {
		ksem_destroy(id);
		return;
	}
	if (!ELAPSED(elapsed, 2500)) {
		fail_err(
	    "ksem_timedwait() of locked sem took %ums instead of 2500ms",
		    elapsed);
		ksem_destroy(id);
		return;
	}
	if (checkvalue(id, 0) < 0) {
		ksem_destroy(id);
		return;
	}

	if (ksem_destroy(id) < 0) {
		fail_errno("ksem_destroy");
		return;
	}
	pass();
}