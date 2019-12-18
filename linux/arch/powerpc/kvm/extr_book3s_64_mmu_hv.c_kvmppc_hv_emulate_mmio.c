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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned long paddr_accessed; int /*<<< orphan*/  vaddr_accessed; } ;
struct kvm_vcpu {TYPE_1__ arch; TYPE_2__* kvm; } ;
struct kvm_run {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_4__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 scalar_t__ EMULATE_DONE ; 
 int /*<<< orphan*/  INST_GENERIC ; 
 int /*<<< orphan*/  KVM_FAST_MMIO_BUS ; 
 int RESUME_GUEST ; 
 int instruction_is_store (int /*<<< orphan*/ ) ; 
 int kvm_io_bus_write (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kvmppc_emulate_mmio (struct kvm_run*,struct kvm_vcpu*) ; 
 scalar_t__ kvmppc_get_last_inst (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_pc (struct kvm_vcpu*,scalar_t__) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

int kvmppc_hv_emulate_mmio(struct kvm_run *run, struct kvm_vcpu *vcpu,
			   unsigned long gpa, gva_t ea, int is_store)
{
	u32 last_inst;

	/*
	 * Fast path - check if the guest physical address corresponds to a
	 * device on the FAST_MMIO_BUS, if so we can avoid loading the
	 * instruction all together, then we can just handle it and return.
	 */
	if (is_store) {
		int idx, ret;

		idx = srcu_read_lock(&vcpu->kvm->srcu);
		ret = kvm_io_bus_write(vcpu, KVM_FAST_MMIO_BUS, (gpa_t) gpa, 0,
				       NULL);
		srcu_read_unlock(&vcpu->kvm->srcu, idx);
		if (!ret) {
			kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);
			return RESUME_GUEST;
		}
	}

	/*
	 * If we fail, we just return to the guest and try executing it again.
	 */
	if (kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst) !=
		EMULATE_DONE)
		return RESUME_GUEST;

	/*
	 * WARNING: We do not know for sure whether the instruction we just
	 * read from memory is the same that caused the fault in the first
	 * place.  If the instruction we read is neither an load or a store,
	 * then it can't access memory, so we don't need to worry about
	 * enforcing access permissions.  So, assuming it is a load or
	 * store, we just check that its direction (load or store) is
	 * consistent with the original fault, since that's what we
	 * checked the access permissions against.  If there is a mismatch
	 * we just return and retry the instruction.
	 */

	if (instruction_is_store(last_inst) != !!is_store)
		return RESUME_GUEST;

	/*
	 * Emulated accesses are emulated by looking at the hash for
	 * translation once, then performing the access later. The
	 * translation could be invalidated in the meantime in which
	 * point performing the subsequent memory access on the old
	 * physical address could possibly be a security hole for the
	 * guest (but not the host).
	 *
	 * This is less of an issue for MMIO stores since they aren't
	 * globally visible. It could be an issue for MMIO loads to
	 * a certain extent but we'll ignore it for now.
	 */

	vcpu->arch.paddr_accessed = gpa;
	vcpu->arch.vaddr_accessed = ea;
	return kvmppc_emulate_mmio(run, vcpu);
}