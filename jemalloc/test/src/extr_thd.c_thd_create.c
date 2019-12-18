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
typedef  int /*<<< orphan*/  thd_t ;

/* Variables and functions */
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  test_fail (char*) ; 

void
thd_create(thd_t *thd, void *(*proc)(void *), void *arg) {
	if (pthread_create(thd, NULL, proc, arg) != 0) {
		test_fail("Error in pthread_create()\n");
	}
}