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
struct pt_regs {int pstate; } ;

/* Variables and functions */
 unsigned int ESR_ELx_EC (unsigned int) ; 
 unsigned int ESR_ELx_EC_DABT_CUR ; 
 unsigned int ESR_ELx_EC_IABT_CUR ; 
 unsigned int ESR_ELx_FSC_FAULT ; 
 unsigned int ESR_ELx_FSC_PERM ; 
 unsigned int ESR_ELx_FSC_TYPE ; 
 int PSR_PAN_BIT ; 
 scalar_t__ is_ttbr0_addr (unsigned long) ; 
 scalar_t__ system_uses_ttbr0_pan () ; 

__attribute__((used)) static inline bool is_el1_permission_fault(unsigned long addr, unsigned int esr,
					   struct pt_regs *regs)
{
	unsigned int ec       = ESR_ELx_EC(esr);
	unsigned int fsc_type = esr & ESR_ELx_FSC_TYPE;

	if (ec != ESR_ELx_EC_DABT_CUR && ec != ESR_ELx_EC_IABT_CUR)
		return false;

	if (fsc_type == ESR_ELx_FSC_PERM)
		return true;

	if (is_ttbr0_addr(addr) && system_uses_ttbr0_pan())
		return fsc_type == ESR_ELx_FSC_FAULT &&
			(regs->pstate & PSR_PAN_BIT);

	return false;
}