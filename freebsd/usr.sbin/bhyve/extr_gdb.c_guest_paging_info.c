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
typedef  int uint64_t ;
struct vm_guest_paging {int cr3; int /*<<< orphan*/  paging_mode; int /*<<< orphan*/  cpu_mode; scalar_t__ cpl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_MODE_64BIT ; 
 int /*<<< orphan*/  CPU_MODE_PROTECTED ; 
 int /*<<< orphan*/  CPU_MODE_REAL ; 
 int CR0_PE ; 
 int CR0_PG ; 
 int CR4_PAE ; 
 int EFER_LMA ; 
 int EFER_LME ; 
 int /*<<< orphan*/  PAGING_MODE_32 ; 
 int /*<<< orphan*/  PAGING_MODE_64 ; 
 int /*<<< orphan*/  PAGING_MODE_FLAT ; 
 int /*<<< orphan*/  PAGING_MODE_PAE ; 
 int const VM_REG_GUEST_CR0 ; 
 int const VM_REG_GUEST_CR3 ; 
 int const VM_REG_GUEST_CR4 ; 
 int const VM_REG_GUEST_EFER ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  nitems (int const*) ; 
 int vm_get_register_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int const*,int*) ; 

__attribute__((used)) static int
guest_paging_info(int vcpu, struct vm_guest_paging *paging)
{
	uint64_t regs[4];
	const int regset[4] = {
		VM_REG_GUEST_CR0,
		VM_REG_GUEST_CR3,
		VM_REG_GUEST_CR4,
		VM_REG_GUEST_EFER
	};

	if (vm_get_register_set(ctx, vcpu, nitems(regset), regset, regs) == -1)
		return (-1);

	/*
	 * For the debugger, always pretend to be the kernel (CPL 0),
	 * and if long-mode is enabled, always parse addresses as if
	 * in 64-bit mode.
	 */
	paging->cr3 = regs[1];
	paging->cpl = 0;
	if (regs[3] & EFER_LMA)
		paging->cpu_mode = CPU_MODE_64BIT;
	else if (regs[0] & CR0_PE)
		paging->cpu_mode = CPU_MODE_PROTECTED;
	else
		paging->cpu_mode = CPU_MODE_REAL;
	if (!(regs[0] & CR0_PG))
		paging->paging_mode = PAGING_MODE_FLAT;
	else if (!(regs[2] & CR4_PAE))
		paging->paging_mode = PAGING_MODE_32;
	else if (regs[3] & EFER_LME)
		paging->paging_mode = PAGING_MODE_64;
	else
		paging->paging_mode = PAGING_MODE_PAE;
	return (0);
}