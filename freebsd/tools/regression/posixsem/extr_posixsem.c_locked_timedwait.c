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
 scalar_t__ check_alarm (int) ; 
 int /*<<< orphan*/  fail_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ ksem_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass () ; 
 scalar_t__ schedule_post (int /*<<< orphan*/ ,int) ; 
 scalar_t__ timedwait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
locked_timedwait(void)
{
	semid_t id;
	u_int elapsed;

	if (ksem_init(&id, 0) < 0) {
		fail_errno("ksem_init");
		return;
	}

	/*
	 * Schedule a post to trigger after 1000 ms.  The subsequent
	 * timedwait should succeed after 1000 ms as a result w/o
	 * timing out.
	 */
	if (schedule_post(id, 1000) < 0) {
		ksem_destroy(id);
		return;
	}
	if (timedwait(id, 2000, &elapsed, 0) < 0) {
		check_alarm(1);
		ksem_destroy(id);
		return;
	}
	if (!ELAPSED(elapsed, 1000)) {
		fail_err(
	    "ksem_timedwait() with delayed post took %ums instead of 1000ms",
		    elapsed);
		check_alarm(1);
		ksem_destroy(id);
		return;
	}
	if (check_alarm(0) < 0) {
		ksem_destroy(id);
		return;
	}

	if (ksem_destroy(id) < 0) {
		fail_errno("ksem_destroy");
		return;
	}
	pass();
}