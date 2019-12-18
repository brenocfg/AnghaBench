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
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_section_detach (struct pt_section*,struct pt_image_section_cache*) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result detach_null(void)
{
	struct pt_image_section_cache iscache;
	struct pt_section section;
	int errcode;

	errcode = pt_section_detach(NULL, &iscache);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_section_detach(&section, NULL);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_section_detach(NULL, NULL);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}