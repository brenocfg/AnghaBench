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
struct ptunit_result {int dummy; } ;
struct iscache_fixture {int /*<<< orphan*/ * section; int /*<<< orphan*/  iscache; } ;

/* Variables and functions */
 int pt_iscache_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_ne (int,int) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result
add_different_same_laddr(struct iscache_fixture *cfix)
{
	int isid[2];

	isid[0] = pt_iscache_add(&cfix->iscache, cfix->section[0], 0ull);
	ptu_int_gt(isid[0], 0);

	isid[1] = pt_iscache_add(&cfix->iscache, cfix->section[1], 0ull);
	ptu_int_gt(isid[1], 0);

	/* We must get different identifiers. */
	ptu_int_ne(isid[1], isid[0]);

	return ptu_passed();
}