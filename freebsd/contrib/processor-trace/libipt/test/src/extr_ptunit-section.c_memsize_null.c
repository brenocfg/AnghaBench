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
struct section_fixture {int /*<<< orphan*/ * section; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_section_memsize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result memsize_null(struct section_fixture *sfix)
{
	uint64_t size;
	int errcode;

	errcode = pt_section_memsize(NULL, &size);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_section_memsize(sfix->section, NULL);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_section_memsize(NULL, NULL);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}