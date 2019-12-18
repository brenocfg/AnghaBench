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
struct iscache_fixture {TYPE_1__** section; int /*<<< orphan*/  iscache; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int pt_iscache_add (int /*<<< orphan*/ *,TYPE_1__*,unsigned long long) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result add_same(struct iscache_fixture *cfix)
{
	int isid[2];

	isid[0] = pt_iscache_add(&cfix->iscache, cfix->section[0], 0ull);
	ptu_int_gt(isid[0], 0);

	cfix->section[1]->offset = cfix->section[0]->offset;
	cfix->section[1]->size = cfix->section[0]->size;

	isid[1] = pt_iscache_add(&cfix->iscache, cfix->section[1], 0ull);
	ptu_int_gt(isid[1], 0);

	/* The second add should be ignored. */
	ptu_int_eq(isid[1], isid[0]);

	return ptu_passed();
}