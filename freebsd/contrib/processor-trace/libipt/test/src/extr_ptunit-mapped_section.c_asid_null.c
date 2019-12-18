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
struct pt_asid {int /*<<< orphan*/  vmcs; int /*<<< orphan*/  cr3; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_asid_no_cr3 ; 
 int /*<<< orphan*/  pt_asid_no_vmcs ; 
 struct pt_asid* pt_msec_asid (struct pt_mapped_section*) ; 
 int /*<<< orphan*/  pt_msec_init (struct pt_mapped_section*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_asid const*) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result asid_null(void)
{
	struct pt_mapped_section msec;
	const struct pt_asid *pasid;

	pt_msec_init(&msec, NULL, NULL, 0x2000ull, 0x100ull, 0x1000ull);

	pasid = pt_msec_asid(&msec);
	ptu_ptr(pasid);
	ptu_uint_eq(pasid->cr3, pt_asid_no_cr3);
	ptu_uint_eq(pasid->vmcs, pt_asid_no_vmcs);

	return ptu_passed();
}