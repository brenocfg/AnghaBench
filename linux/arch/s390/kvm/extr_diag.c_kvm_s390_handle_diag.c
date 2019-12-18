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
struct TYPE_8__ {int /*<<< orphan*/  diagnose_other; } ;
struct TYPE_7__ {TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_4__ stat; TYPE_3__ arch; } ;
struct TYPE_5__ {int mask; } ;
struct TYPE_6__ {TYPE_1__ gpsw; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PGM_PRIVILEGED_OP ; 
 int PSW_MASK_PSTATE ; 
 int __diag_ipl_functions (struct kvm_vcpu*) ; 
 int __diag_page_ref_service (struct kvm_vcpu*) ; 
 int __diag_time_slice_end (struct kvm_vcpu*) ; 
 int __diag_time_slice_end_directed (struct kvm_vcpu*) ; 
 int __diag_virtio_hypercall (struct kvm_vcpu*) ; 
 int diag_release_pages (struct kvm_vcpu*) ; 
 int kvm_s390_get_base_disp_rs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int kvm_s390_inject_program_int (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_s390_handle_diag (struct kvm_vcpu*,int) ; 

int kvm_s390_handle_diag(struct kvm_vcpu *vcpu)
{
	int code = kvm_s390_get_base_disp_rs(vcpu, NULL) & 0xffff;

	if (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		return kvm_s390_inject_program_int(vcpu, PGM_PRIVILEGED_OP);

	trace_kvm_s390_handle_diag(vcpu, code);
	switch (code) {
	case 0x10:
		return diag_release_pages(vcpu);
	case 0x44:
		return __diag_time_slice_end(vcpu);
	case 0x9c:
		return __diag_time_slice_end_directed(vcpu);
	case 0x258:
		return __diag_page_ref_service(vcpu);
	case 0x308:
		return __diag_ipl_functions(vcpu);
	case 0x500:
		return __diag_virtio_hypercall(vcpu);
	default:
		vcpu->stat.diagnose_other++;
		return -EOPNOTSUPP;
	}
}