#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvm {int dummy; } ;
struct TYPE_4__ {int msa_id; } ;
struct TYPE_3__ {int (* check_extension ) (struct kvm*,long) ;} ;

/* Variables and functions */
#define  KVM_CAP_ENABLE_CAP 137 
#define  KVM_CAP_IMMEDIATE_EXIT 136 
#define  KVM_CAP_MAX_VCPUS 135 
#define  KVM_CAP_MAX_VCPU_ID 134 
#define  KVM_CAP_MIPS_FPU 133 
#define  KVM_CAP_MIPS_MSA 132 
#define  KVM_CAP_NR_VCPUS 131 
#define  KVM_CAP_ONE_REG 130 
#define  KVM_CAP_READONLY_MEM 129 
#define  KVM_CAP_SYNC_MMU 128 
 int KVM_MAX_VCPUS ; 
 int KVM_MAX_VCPU_ID ; 
 int MSA_IR_WRPF ; 
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  cpu_has_msa ; 
 TYPE_1__* kvm_mips_callbacks ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  raw_cpu_has_fpu ; 
 int stub1 (struct kvm*,long) ; 

int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
{
	int r;

	switch (ext) {
	case KVM_CAP_ONE_REG:
	case KVM_CAP_ENABLE_CAP:
	case KVM_CAP_READONLY_MEM:
	case KVM_CAP_SYNC_MMU:
	case KVM_CAP_IMMEDIATE_EXIT:
		r = 1;
		break;
	case KVM_CAP_NR_VCPUS:
		r = num_online_cpus();
		break;
	case KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		break;
	case KVM_CAP_MAX_VCPU_ID:
		r = KVM_MAX_VCPU_ID;
		break;
	case KVM_CAP_MIPS_FPU:
		/* We don't handle systems with inconsistent cpu_has_fpu */
		r = !!raw_cpu_has_fpu;
		break;
	case KVM_CAP_MIPS_MSA:
		/*
		 * We don't support MSA vector partitioning yet:
		 * 1) It would require explicit support which can't be tested
		 *    yet due to lack of support in current hardware.
		 * 2) It extends the state that would need to be saved/restored
		 *    by e.g. QEMU for migration.
		 *
		 * When vector partitioning hardware becomes available, support
		 * could be added by requiring a flag when enabling
		 * KVM_CAP_MIPS_MSA capability to indicate that userland knows
		 * to save/restore the appropriate extra state.
		 */
		r = cpu_has_msa && !(boot_cpu_data.msa_id & MSA_IR_WRPF);
		break;
	default:
		r = kvm_mips_callbacks->check_extension(kvm, ext);
		break;
	}
	return r;
}