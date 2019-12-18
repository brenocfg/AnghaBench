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
struct pt_mapped_section {int dummy; } ;
struct image_fixture {int /*<<< orphan*/ * asid; int /*<<< orphan*/  image; } ;

/* Variables and functions */
 int pt_image_find (int /*<<< orphan*/ *,struct pt_mapped_section*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pte_nomap ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result find_bad_asid(struct image_fixture *ifix)
{
	struct pt_mapped_section msec;
	int status;

	status = pt_image_find(&ifix->image, &msec, &ifix->asid[0], 0x2003ull);
	ptu_int_eq(status, -pte_nomap);

	return ptu_passed();
}