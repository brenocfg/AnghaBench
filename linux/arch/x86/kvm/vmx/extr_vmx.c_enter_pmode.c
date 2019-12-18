#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long save_rflags; int /*<<< orphan*/ * segs; scalar_t__ vm86_active; } ;
struct vcpu_vmx {TYPE_1__ rmode; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR4_READ_SHADOW ; 
 int /*<<< orphan*/  GUEST_CR4 ; 
 int /*<<< orphan*/  GUEST_RFLAGS ; 
 unsigned long RMODE_GUEST_OWNED_EFLAGS_BITS ; 
 size_t VCPU_SREG_CS ; 
 size_t VCPU_SREG_DS ; 
 size_t VCPU_SREG_ES ; 
 size_t VCPU_SREG_FS ; 
 size_t VCPU_SREG_GS ; 
 size_t VCPU_SREG_SS ; 
 size_t VCPU_SREG_TR ; 
 unsigned long X86_CR4_VME ; 
 int /*<<< orphan*/  fix_pmode_seg (struct kvm_vcpu*,size_t,int /*<<< orphan*/ *) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_exception_bitmap (struct kvm_vcpu*) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vmx_get_segment (struct kvm_vcpu*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vmx_segment_cache_clear (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_set_segment (struct kvm_vcpu*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void enter_pmode(struct kvm_vcpu *vcpu)
{
	unsigned long flags;
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * Update real mode segment cache. It may be not up-to-date if sement
	 * register was written while vcpu was in a guest mode.
	 */
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_ES], VCPU_SREG_ES);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_DS], VCPU_SREG_DS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_FS], VCPU_SREG_FS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_GS], VCPU_SREG_GS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_SS], VCPU_SREG_SS);
	vmx_get_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_CS], VCPU_SREG_CS);

	vmx->rmode.vm86_active = 0;

	vmx_segment_cache_clear(vmx);

	vmx_set_segment(vcpu, &vmx->rmode.segs[VCPU_SREG_TR], VCPU_SREG_TR);

	flags = vmcs_readl(GUEST_RFLAGS);
	flags &= RMODE_GUEST_OWNED_EFLAGS_BITS;
	flags |= vmx->rmode.save_rflags & ~RMODE_GUEST_OWNED_EFLAGS_BITS;
	vmcs_writel(GUEST_RFLAGS, flags);

	vmcs_writel(GUEST_CR4, (vmcs_readl(GUEST_CR4) & ~X86_CR4_VME) |
			(vmcs_readl(CR4_READ_SHADOW) & X86_CR4_VME));

	update_exception_bitmap(vcpu);

	fix_pmode_seg(vcpu, VCPU_SREG_CS, &vmx->rmode.segs[VCPU_SREG_CS]);
	fix_pmode_seg(vcpu, VCPU_SREG_SS, &vmx->rmode.segs[VCPU_SREG_SS]);
	fix_pmode_seg(vcpu, VCPU_SREG_ES, &vmx->rmode.segs[VCPU_SREG_ES]);
	fix_pmode_seg(vcpu, VCPU_SREG_DS, &vmx->rmode.segs[VCPU_SREG_DS]);
	fix_pmode_seg(vcpu, VCPU_SREG_FS, &vmx->rmode.segs[VCPU_SREG_FS]);
	fix_pmode_seg(vcpu, VCPU_SREG_GS, &vmx->rmode.segs[VCPU_SREG_GS]);
}