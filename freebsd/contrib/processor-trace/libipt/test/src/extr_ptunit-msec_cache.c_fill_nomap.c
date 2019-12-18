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
struct TYPE_3__ {int /*<<< orphan*/  ucount; int /*<<< orphan*/  mcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  msec; } ;
struct test_fixture {TYPE_1__ section; TYPE_2__ mcache; int /*<<< orphan*/  image; } ;
struct ptunit_result {int dummy; } ;
typedef  struct pt_section const pt_section ;
typedef  struct pt_section pt_mapped_section ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pt_msec_cache_fill (TYPE_2__*,struct pt_section const**,int /*<<< orphan*/ *,struct pt_asid*,unsigned long long) ; 
 struct pt_section* pt_msec_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_nomap ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_null (struct pt_section const*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result fill_nomap(struct test_fixture *tfix)
{
	const struct pt_mapped_section *msec;
	struct pt_asid asid;
	struct pt_section *section;
	int status;

	msec = NULL;

	status = pt_msec_cache_fill(&tfix->mcache, &msec, &tfix->image, &asid,
				    0ull);
	ptu_int_eq(status, -pte_nomap);

	section = pt_msec_section(&tfix->mcache.msec);
	ptu_null(section);
	ptu_null(msec);

	ptu_uint_eq(tfix->section.mcount, 0);
	ptu_uint_eq(tfix->section.ucount, 0);

	return ptu_passed();
}