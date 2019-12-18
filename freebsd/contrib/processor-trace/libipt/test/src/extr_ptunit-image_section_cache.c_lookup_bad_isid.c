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
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct pt_section {int dummy; } ;
struct iscache_fixture {int /*<<< orphan*/  iscache; int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 int pt_iscache_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long long) ; 
 int pt_iscache_lookup (int /*<<< orphan*/ *,struct pt_section**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pte_bad_image ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result lookup_bad_isid(struct iscache_fixture *cfix)
{
	struct pt_section *section;
	uint64_t laddr;
	int errcode, isid;

	isid = pt_iscache_add(&cfix->iscache, cfix->section[0], 0ull);
	ptu_int_gt(isid, 0);

	errcode = pt_iscache_lookup(&cfix->iscache, &section, &laddr, 0);
	ptu_int_eq(errcode, -pte_bad_image);

	errcode = pt_iscache_lookup(&cfix->iscache, &section, &laddr, -isid);
	ptu_int_eq(errcode, -pte_bad_image);

	errcode = pt_iscache_lookup(&cfix->iscache, &section, &laddr, isid + 1);
	ptu_int_eq(errcode, -pte_bad_image);

	return ptu_passed();
}