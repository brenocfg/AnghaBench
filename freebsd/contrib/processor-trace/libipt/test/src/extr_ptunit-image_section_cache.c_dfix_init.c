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
struct pt_section {int dummy; } ;
struct iscache_fixture {struct pt_section** section; int /*<<< orphan*/  thrd; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_section**,int /*<<< orphan*/ ,int) ; 
 int num_sections ; 
 int pt_mk_section (struct pt_section**,char*,int,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_section*) ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptunit_thrd_init ; 

__attribute__((used)) static struct ptunit_result dfix_init(struct iscache_fixture *cfix)
{
	int idx;

	ptu_test(ptunit_thrd_init, &cfix->thrd);

	memset(cfix->section, 0, sizeof(cfix->section));

	for (idx = 0; idx < num_sections; ++idx) {
		struct pt_section *section;
		int errcode;

		errcode = pt_mk_section(&section, "some-filename",
					idx % 3 == 0 ? 0x1000 : 0x2000,
					idx % 2 == 0 ? 0x1000 : 0x2000);
		ptu_int_eq(errcode, 0);
		ptu_ptr(section);

		cfix->section[idx] = section;
	}

	return ptu_passed();
}