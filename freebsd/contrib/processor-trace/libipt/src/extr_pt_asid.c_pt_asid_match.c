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
typedef  scalar_t__ uint64_t ;
struct pt_asid {scalar_t__ cr3; scalar_t__ vmcs; } ;

/* Variables and functions */
 scalar_t__ pt_asid_no_cr3 ; 
 scalar_t__ pt_asid_no_vmcs ; 
 int pte_internal ; 

int pt_asid_match(const struct pt_asid *lhs, const struct pt_asid *rhs)
{
	uint64_t lcr3, rcr3, lvmcs, rvmcs;

	if (!lhs || !rhs)
		return -pte_internal;

	lcr3 = lhs->cr3;
	rcr3 = rhs->cr3;

	if (lcr3 != rcr3 && lcr3 != pt_asid_no_cr3 && rcr3 != pt_asid_no_cr3)
		return 0;

	lvmcs = lhs->vmcs;
	rvmcs = rhs->vmcs;

	if (lvmcs != rvmcs && lvmcs != pt_asid_no_vmcs &&
	    rvmcs != pt_asid_no_vmcs)
		return 0;

	return 1;
}