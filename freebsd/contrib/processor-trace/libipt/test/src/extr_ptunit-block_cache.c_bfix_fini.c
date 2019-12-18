#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_2__ {int nthreads; int /*<<< orphan*/ * result; } ;
struct bcache_fixture {int /*<<< orphan*/  bcache; TYPE_1__ thrd; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_bcache_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ptunit_thrd_fini ; 

__attribute__((used)) static struct ptunit_result bfix_fini(struct bcache_fixture *bfix)
{
	int thrd;

	ptu_test(ptunit_thrd_fini, &bfix->thrd);

	for (thrd = 0; thrd < bfix->thrd.nthreads; ++thrd)
		ptu_int_eq(bfix->thrd.result[thrd], 0);

	pt_bcache_free(bfix->bcache);

	return ptu_passed();
}