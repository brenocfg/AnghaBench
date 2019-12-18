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
struct pt_asid {int vmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_asid_init (struct pt_asid*) ; 
 int pt_asid_match (struct pt_asid*,struct pt_asid*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result match_vmcs(void)
{
	struct pt_asid lhs, rhs;
	int errcode;

	pt_asid_init(&lhs);
	pt_asid_init(&rhs);

	lhs.vmcs = 0x23000ull;
	rhs.vmcs = 0x23000ull;

	errcode = pt_asid_match(&lhs, &rhs);
	ptu_int_eq(errcode, 1);

	return ptu_passed();
}