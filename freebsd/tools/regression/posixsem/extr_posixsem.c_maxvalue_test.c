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
 int SEM_VALUE_MAX ; 
 int /*<<< orphan*/  fail_err (char*) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ ksem_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_getvalue (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ksem_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pass () ; 

__attribute__((used)) static void
maxvalue_test(void)
{
	semid_t id;
	int val;

	if (ksem_init(&id, SEM_VALUE_MAX) < 0) {
		fail_errno("ksem_init");
		return;
	}
	if (ksem_getvalue(id, &val) < 0) {
		fail_errno("ksem_getvalue");
		ksem_destroy(id);
		return;
	}
	if (val != SEM_VALUE_MAX) {
		fail_err("value %d != SEM_VALUE_MAX");
		ksem_destroy(id);
		return;
	}
	if (val < 0) {
		fail_err("value < 0");
		ksem_destroy(id);
		return;
	}
	if (ksem_destroy(id) < 0) {
		fail_errno("ksem_destroy");
		return;
	}
	pass();
}