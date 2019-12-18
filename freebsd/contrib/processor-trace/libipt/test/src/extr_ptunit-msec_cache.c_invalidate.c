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
struct test_fixture {TYPE_1__ section; TYPE_2__ mcache; } ;
struct ptunit_result {int dummy; } ;
struct pt_section {int dummy; } ;

/* Variables and functions */
 int pt_msec_cache_invalidate (TYPE_2__*) ; 
 struct pt_section* pt_msec_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_null (struct pt_section*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result invalidate(struct test_fixture *tfix)
{
	struct pt_section *section;
	int status;

	status = pt_msec_cache_invalidate(&tfix->mcache);
	ptu_int_eq(status, 0);

	section = pt_msec_section(&tfix->mcache.msec);
	ptu_null(section);

	ptu_uint_eq(tfix->section.mcount, 0);
	ptu_uint_eq(tfix->section.ucount, 0);

	return ptu_passed();
}