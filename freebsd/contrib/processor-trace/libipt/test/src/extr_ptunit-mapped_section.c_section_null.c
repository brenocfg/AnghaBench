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
struct pt_mapped_section {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_msec_init (struct pt_mapped_section*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 struct pt_section* pt_msec_section (struct pt_mapped_section*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (struct pt_section*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ptunit_result section_null(void)
{
	struct pt_mapped_section msec;
	struct pt_section *psection;

	pt_msec_init(&msec, NULL, NULL, 0x2000ull, 0x100ull, 0x1000ull);

	psection = pt_msec_section(&msec);
	ptu_ptr_eq(psection, NULL);

	return ptu_passed();
}