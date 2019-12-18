#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_3__ {int nthreads; int* result; } ;
struct iscache_fixture {TYPE_2__** section; int /*<<< orphan*/  iscache; TYPE_1__ thrd; } ;
struct TYPE_4__ {int ucount; int acount; int mcount; int /*<<< orphan*/  iscache; } ;

/* Variables and functions */
 int num_sections ; 
 int /*<<< orphan*/  pt_iscache_fini (int /*<<< orphan*/ *) ; 
 int pt_section_put (TYPE_2__*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 int /*<<< orphan*/  ptu_null (int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ptunit_thrd_fini ; 

__attribute__((used)) static struct ptunit_result cfix_fini(struct iscache_fixture *cfix)
{
	int idx, errcode;

	ptu_test(ptunit_thrd_fini, &cfix->thrd);

	for (idx = 0; idx < cfix->thrd.nthreads; ++idx)
		ptu_int_eq(cfix->thrd.result[idx], 0);

	pt_iscache_fini(&cfix->iscache);

	for (idx = 0; idx < num_sections; ++idx) {
		ptu_int_eq(cfix->section[idx]->ucount, 1);
		ptu_int_eq(cfix->section[idx]->acount, 0);
		ptu_int_eq(cfix->section[idx]->mcount, 0);
		ptu_null(cfix->section[idx]->iscache);

		errcode = pt_section_put(cfix->section[idx]);
		ptu_int_eq(errcode, 0);
	}

	return ptu_passed();
}