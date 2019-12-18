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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int CR0_NE ; 
 int CR0_PE ; 
 int CR0_PG ; 
 int CR4_PAE ; 
 int DESC_UNUSABLE ; 
 int EFER_LMA ; 
 int EFER_LME ; 
 int GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUEST_CODE_SEL ; 
 int /*<<< orphan*/  GUEST_DATA_SEL ; 
 int GUEST_GDTR_LIMIT64 ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR0 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR3 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR4 ; 
 int /*<<< orphan*/  VM_REG_GUEST_CS ; 
 int /*<<< orphan*/  VM_REG_GUEST_DS ; 
 int /*<<< orphan*/  VM_REG_GUEST_EFER ; 
 int /*<<< orphan*/  VM_REG_GUEST_ES ; 
 int /*<<< orphan*/  VM_REG_GUEST_FS ; 
 int /*<<< orphan*/  VM_REG_GUEST_GDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_GS ; 
 int /*<<< orphan*/  VM_REG_GUEST_LDTR ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RIP ; 
 int /*<<< orphan*/  VM_REG_GUEST_RSP ; 
 int /*<<< orphan*/  VM_REG_GUEST_SS ; 
 int /*<<< orphan*/  VM_REG_GUEST_TR ; 
 int vm_set_desc (struct vmctx*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int vm_set_register (struct vmctx*,int,int /*<<< orphan*/ ,int) ; 

int
vm_setup_freebsd_registers(struct vmctx *vmctx, int vcpu,
			   uint64_t rip, uint64_t cr3, uint64_t gdtbase,
			   uint64_t rsp)
{
	int error;
	uint64_t cr0, cr4, efer, rflags, desc_base;
	uint32_t desc_access, desc_limit;
	uint16_t gsel;

	cr0 = CR0_PE | CR0_PG | CR0_NE;
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_CR0, cr0)) != 0)
		goto done;

	cr4 = CR4_PAE;
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_CR4, cr4)) != 0)
		goto done;

	efer = EFER_LME | EFER_LMA;
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_EFER, efer)))
		goto done;

	rflags = 0x2;
	error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_RFLAGS, rflags);
	if (error)
		goto done;

	desc_base = 0;
	desc_limit = 0;
	desc_access = 0x0000209B;
	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_CS,
			    desc_base, desc_limit, desc_access);
	if (error)
		goto done;

	desc_access = 0x00000093;
	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_DS,
			    desc_base, desc_limit, desc_access);
	if (error)
		goto done;

	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_ES,
			    desc_base, desc_limit, desc_access);
	if (error)
		goto done;

	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_FS,
			    desc_base, desc_limit, desc_access);
	if (error)
		goto done;

	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_GS,
			    desc_base, desc_limit, desc_access);
	if (error)
		goto done;

	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_SS,
			    desc_base, desc_limit, desc_access);
	if (error)
		goto done;

	/*
	 * XXX TR is pointing to null selector even though we set the
	 * TSS segment to be usable with a base address and limit of 0.
	 */
	desc_access = 0x0000008b;
	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_TR, 0, 0, desc_access);
	if (error)
		goto done;

	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_LDTR, 0, 0,
			    DESC_UNUSABLE);
	if (error)
		goto done;

	gsel = GSEL(GUEST_CODE_SEL, SEL_KPL);
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_CS, gsel)) != 0)
		goto done;
	
	gsel = GSEL(GUEST_DATA_SEL, SEL_KPL);
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_DS, gsel)) != 0)
		goto done;
	
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_ES, gsel)) != 0)
		goto done;

	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_FS, gsel)) != 0)
		goto done;
	
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_GS, gsel)) != 0)
		goto done;
	
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_SS, gsel)) != 0)
		goto done;

	/* XXX TR is pointing to the null selector */
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_TR, 0)) != 0)
		goto done;

	/* LDTR is pointing to the null selector */
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_LDTR, 0)) != 0)
		goto done;

	/* entry point */
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_RIP, rip)) != 0)
		goto done;

	/* page table base */
	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_CR3, cr3)) != 0)
		goto done;

	desc_base = gdtbase;
	desc_limit = GUEST_GDTR_LIMIT64;
	error = vm_set_desc(vmctx, vcpu, VM_REG_GUEST_GDTR,
			    desc_base, desc_limit, 0);
	if (error != 0)
		goto done;

	if ((error = vm_set_register(vmctx, vcpu, VM_REG_GUEST_RSP, rsp)) != 0)
		goto done;

	error = 0;
done:
	return (error);
}