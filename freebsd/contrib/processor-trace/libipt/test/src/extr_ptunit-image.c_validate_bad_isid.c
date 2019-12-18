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
struct pt_mapped_section {int /*<<< orphan*/  section; } ;
struct image_fixture {int /*<<< orphan*/  image; int /*<<< orphan*/ * asid; } ;

/* Variables and functions */
 int pt_image_find (int /*<<< orphan*/ *,struct pt_mapped_section*,int /*<<< orphan*/ *,int) ; 
 int pt_image_validate (int /*<<< orphan*/ *,struct pt_mapped_section*,int,int) ; 
 int pt_section_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_nomap ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_ge (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result validate_bad_isid(struct image_fixture *ifix)
{
	struct pt_mapped_section msec;
	int isid, status;

	isid = pt_image_find(&ifix->image, &msec, &ifix->asid[0], 0x1003ull);
	ptu_int_ge(isid, 0);

	status = pt_section_put(msec.section);
	ptu_int_eq(status, 0);

	status = pt_image_validate(&ifix->image, &msec, 0x1004ull, isid + 1);
	ptu_int_eq(status, -pte_nomap);

	return ptu_passed();
}