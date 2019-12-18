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
struct TYPE_2__ {int /*<<< orphan*/  acount; int /*<<< orphan*/  ucount; } ;

/* Variables and functions */
 int pt_iscache_add (int /*<<< orphan*/ *,TYPE_1__*,unsigned long long) ; 
 int /*<<< orphan*/  ptu_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result add(struct iscache_fixture *cfix)
{
	int isid;

	isid = pt_iscache_add(&cfix->iscache, cfix->section[0], 0ull);
	ptu_int_gt(isid, 0);

	/* The cache attaches and gets a reference on success. */
	ptu_int_eq(cfix->section[0]->ucount, 2);
	ptu_int_eq(cfix->section[0]->acount, 1);

	/* The added section must be implicitly put in pt_iscache_fini. */
	return ptu_passed();
}