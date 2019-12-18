#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvmppc_pte {scalar_t__ may_execute; scalar_t__ may_write; scalar_t__ may_read; } ;
struct TYPE_6__ {unsigned long amr; unsigned long iamr; int /*<<< orphan*/  pid; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_2__* kvm; } ;
typedef  int gva_t ;
struct TYPE_4__ {int /*<<< orphan*/  process_table; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int MSR_PR ; 
 int _PAGE_PRIVILEGED ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int kvmppc_mmu_radix_translate_table (struct kvm_vcpu*,int,struct kvmppc_pte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int kvmppc_mmu_radix_xlate(struct kvm_vcpu *vcpu, gva_t eaddr,
			   struct kvmppc_pte *gpte, bool data, bool iswrite)
{
	u32 pid;
	u64 pte;
	int ret;

	/* Work out effective PID */
	switch (eaddr >> 62) {
	case 0:
		pid = vcpu->arch.pid;
		break;
	case 3:
		pid = 0;
		break;
	default:
		return -EINVAL;
	}

	ret = kvmppc_mmu_radix_translate_table(vcpu, eaddr, gpte,
				vcpu->kvm->arch.process_table, pid, &pte);
	if (ret)
		return ret;

	/* Check privilege (applies only to process scoped translations) */
	if (kvmppc_get_msr(vcpu) & MSR_PR) {
		if (pte & _PAGE_PRIVILEGED) {
			gpte->may_read = 0;
			gpte->may_write = 0;
			gpte->may_execute = 0;
		}
	} else {
		if (!(pte & _PAGE_PRIVILEGED)) {
			/* Check AMR/IAMR to see if strict mode is in force */
			if (vcpu->arch.amr & (1ul << 62))
				gpte->may_read = 0;
			if (vcpu->arch.amr & (1ul << 63))
				gpte->may_write = 0;
			if (vcpu->arch.iamr & (1ul << 62))
				gpte->may_execute = 0;
		}
	}

	return 0;
}