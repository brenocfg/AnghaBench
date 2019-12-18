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
struct pt_section {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  filename; } ;
struct iscache_fixture {int /*<<< orphan*/  iscache; struct pt_section** section; } ;

/* Variables and functions */
 int pt_iscache_add (int /*<<< orphan*/ *,struct pt_section*,unsigned long long) ; 
 int pt_iscache_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_section*) ; 

__attribute__((used)) static struct ptunit_result find_bad_laddr(struct iscache_fixture *cfix)
{
	struct pt_section *section;
	int found, isid;

	section = cfix->section[0];
	ptu_ptr(section);

	isid = pt_iscache_add(&cfix->iscache, section, 0ull);
	ptu_int_gt(isid, 0);

	found = pt_iscache_find(&cfix->iscache, section->filename,
				section->offset, section->size, 1ull);
	ptu_int_eq(found, 0);

	return ptu_passed();
}