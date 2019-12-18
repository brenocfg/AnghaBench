#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {scalar_t__ mmio_vsx_copy_nums; scalar_t__ mmio_vmx_copy_nums; scalar_t__ epr_needed; scalar_t__ hcall_needed; scalar_t__ osi_needed; int /*<<< orphan*/  mmio_vmx_offset; int /*<<< orphan*/  mmio_vsx_offset; } ;
struct kvm_vcpu {int mmio_needed; TYPE_4__ arch; int /*<<< orphan*/  mmio_is_write; } ;
struct TYPE_7__ {int /*<<< orphan*/  epr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * args; int /*<<< orphan*/  ret; } ;
struct TYPE_5__ {int /*<<< orphan*/ * gprs; } ;
struct kvm_run {scalar_t__ immediate_exit; TYPE_3__ epr; TYPE_2__ papr_hcall; TYPE_1__ osi; } ;

/* Variables and functions */
 int EINTR ; 
 int RESUME_HOST ; 
 int /*<<< orphan*/  kvm_sigset_activate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_sigset_deactivate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_complete_mmio_load (struct kvm_vcpu*,struct kvm_run*) ; 
 int kvmppc_emulate_mmio_vmx_loadstore (struct kvm_vcpu*,struct kvm_run*) ; 
 int kvmppc_emulate_mmio_vsx_loadstore (struct kvm_vcpu*,struct kvm_run*) ; 
 int /*<<< orphan*/  kvmppc_set_epr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int kvmppc_vcpu_run (struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	int r;

	vcpu_load(vcpu);

	if (vcpu->mmio_needed) {
		vcpu->mmio_needed = 0;
		if (!vcpu->mmio_is_write)
			kvmppc_complete_mmio_load(vcpu, run);
#ifdef CONFIG_VSX
		if (vcpu->arch.mmio_vsx_copy_nums > 0) {
			vcpu->arch.mmio_vsx_copy_nums--;
			vcpu->arch.mmio_vsx_offset++;
		}

		if (vcpu->arch.mmio_vsx_copy_nums > 0) {
			r = kvmppc_emulate_mmio_vsx_loadstore(vcpu, run);
			if (r == RESUME_HOST) {
				vcpu->mmio_needed = 1;
				goto out;
			}
		}
#endif
#ifdef CONFIG_ALTIVEC
		if (vcpu->arch.mmio_vmx_copy_nums > 0) {
			vcpu->arch.mmio_vmx_copy_nums--;
			vcpu->arch.mmio_vmx_offset++;
		}

		if (vcpu->arch.mmio_vmx_copy_nums > 0) {
			r = kvmppc_emulate_mmio_vmx_loadstore(vcpu, run);
			if (r == RESUME_HOST) {
				vcpu->mmio_needed = 1;
				goto out;
			}
		}
#endif
	} else if (vcpu->arch.osi_needed) {
		u64 *gprs = run->osi.gprs;
		int i;

		for (i = 0; i < 32; i++)
			kvmppc_set_gpr(vcpu, i, gprs[i]);
		vcpu->arch.osi_needed = 0;
	} else if (vcpu->arch.hcall_needed) {
		int i;

		kvmppc_set_gpr(vcpu, 3, run->papr_hcall.ret);
		for (i = 0; i < 9; ++i)
			kvmppc_set_gpr(vcpu, 4 + i, run->papr_hcall.args[i]);
		vcpu->arch.hcall_needed = 0;
#ifdef CONFIG_BOOKE
	} else if (vcpu->arch.epr_needed) {
		kvmppc_set_epr(vcpu, run->epr.epr);
		vcpu->arch.epr_needed = 0;
#endif
	}

	kvm_sigset_activate(vcpu);

	if (run->immediate_exit)
		r = -EINTR;
	else
		r = kvmppc_vcpu_run(run, vcpu);

	kvm_sigset_deactivate(vcpu);

#ifdef CONFIG_ALTIVEC
out:
#endif
	vcpu_put(vcpu);
	return r;
}