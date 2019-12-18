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
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  SEM_VALUE_MAX ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int /*<<< orphan*/  ksem_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_post_should_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maxvalue_post_test(void)
{
	semid_t id;

	if (ksem_init(&id, SEM_VALUE_MAX) < 0) {
		fail_errno("ksem_init");
		return;
	}

	ksem_post_should_fail(id, EOVERFLOW);

	ksem_destroy(id);
}