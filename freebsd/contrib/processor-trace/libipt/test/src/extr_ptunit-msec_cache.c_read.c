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
struct TYPE_2__ {int /*<<< orphan*/  msec; } ;
struct test_fixture {int /*<<< orphan*/  section; TYPE_1__ mcache; int /*<<< orphan*/  image; } ;
struct ptunit_result {int dummy; } ;
typedef  struct pt_section const pt_section ;
typedef  struct pt_section pt_mapped_section ;

/* Variables and functions */
 int pt_msec_cache_read (TYPE_1__*,struct pt_section const**,int /*<<< orphan*/ *,unsigned long long) ; 
 struct pt_section* pt_msec_section (struct pt_section const*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (struct pt_section const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ptunit_result read(struct test_fixture *tfix)
{
	const struct pt_mapped_section *msec;
	struct pt_section *section;
	int status;

	status = pt_msec_cache_read(&tfix->mcache, &msec, &tfix->image, 0ull);
	ptu_int_eq(status, 0);

	ptu_ptr_eq(msec, &tfix->mcache.msec);

	section = pt_msec_section(msec);
	ptu_ptr_eq(section, &tfix->section);

	return ptu_passed();
}