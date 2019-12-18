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
struct TYPE_2__ {int limit; } ;
struct iscache_fixture {int /*<<< orphan*/ * section; TYPE_1__ iscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfix_init ; 
 int num_sections ; 
 int pt_iscache_add (TYPE_1__*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ptu_int_ge (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct iscache_fixture*) ; 

__attribute__((used)) static struct ptunit_result sfix_init(struct iscache_fixture *cfix)
{
	int status, idx;

	ptu_test(cfix_init, cfix);

	cfix->iscache.limit = 0x7800;

	for (idx = 0; idx < num_sections; ++idx) {
		status = pt_iscache_add(&cfix->iscache, cfix->section[idx],
					0ull);
		ptu_int_ge(status, 0);
	}

	return ptu_passed();
}