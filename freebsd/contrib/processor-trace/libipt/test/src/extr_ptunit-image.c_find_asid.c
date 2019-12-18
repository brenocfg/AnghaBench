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
struct pt_mapped_section {int /*<<< orphan*/  section; int /*<<< orphan*/  vaddr; } ;
struct image_fixture {int /*<<< orphan*/ * section; int /*<<< orphan*/ * asid; int /*<<< orphan*/  image; } ;

/* Variables and functions */
 int pt_image_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int pt_image_find (int /*<<< orphan*/ *,struct pt_mapped_section*,int /*<<< orphan*/ *,int) ; 
 int pt_section_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result find_asid(struct image_fixture *ifix)
{
	struct pt_mapped_section msec;
	int status;

	status = pt_image_add(&ifix->image, &ifix->section[0], &ifix->asid[0],
			      0x1000ull, 1);
	ptu_int_eq(status, 0);

	status = pt_image_add(&ifix->image, &ifix->section[0], &ifix->asid[1],
			      0x1008ull, 2);
	ptu_int_eq(status, 0);

	status = pt_image_find(&ifix->image, &msec, &ifix->asid[0], 0x1009ull);
	ptu_int_eq(status, 1);
	ptu_ptr_eq(msec.section, &ifix->section[0]);
	ptu_uint_eq(msec.vaddr, 0x1000ull);

	status = pt_section_put(msec.section);
	ptu_int_eq(status, 0);

	status = pt_image_find(&ifix->image, &msec, &ifix->asid[1], 0x1009ull);
	ptu_int_eq(status, 2);
	ptu_ptr_eq(msec.section, &ifix->section[0]);
	ptu_uint_eq(msec.vaddr, 0x1008ull);

	status = pt_section_put(msec.section);
	ptu_int_eq(status, 0);

	return ptu_passed();
}