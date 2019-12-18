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
struct mm_struct {int dummy; } ;
struct TYPE_3__ {int last_exec_cpu; int* vzguestid; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  asid_flush_mask; struct mm_struct gpa_mm; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUESTID_MASK ; 
 int GUESTID_VERSION_MASK ; 
 int /*<<< orphan*/  change_c0_guestctl1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_mmu_context (struct mm_struct*) ; 
 scalar_t__ cpu_has_guestid ; 
 scalar_t__ cpumask_test_and_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_new_mmu_context (struct mm_struct*) ; 
 int guestid_cache (int) ; 
 int /*<<< orphan*/  kvm_vz_get_new_guestid (int,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vz_local_flush_guesttlb_all () ; 
 struct kvm_vcpu** last_exec_vcpu ; 
 int /*<<< orphan*/  trace_kvm_guestid_change (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void kvm_vz_vcpu_load_tlb(struct kvm_vcpu *vcpu, int cpu)
{
	struct kvm *kvm = vcpu->kvm;
	struct mm_struct *gpa_mm = &kvm->arch.gpa_mm;
	bool migrated;

	/*
	 * Are we entering guest context on a different CPU to last time?
	 * If so, the VCPU's guest TLB state on this CPU may be stale.
	 */
	migrated = (vcpu->arch.last_exec_cpu != cpu);
	vcpu->arch.last_exec_cpu = cpu;

	/*
	 * A vcpu's GuestID is set in GuestCtl1.ID when the vcpu is loaded and
	 * remains set until another vcpu is loaded in.  As a rule GuestRID
	 * remains zeroed when in root context unless the kernel is busy
	 * manipulating guest tlb entries.
	 */
	if (cpu_has_guestid) {
		/*
		 * Check if our GuestID is of an older version and thus invalid.
		 *
		 * We also discard the stored GuestID if we've executed on
		 * another CPU, as the guest mappings may have changed without
		 * hypervisor knowledge.
		 */
		if (migrated ||
		    (vcpu->arch.vzguestid[cpu] ^ guestid_cache(cpu)) &
					GUESTID_VERSION_MASK) {
			kvm_vz_get_new_guestid(cpu, vcpu);
			vcpu->arch.vzguestid[cpu] = guestid_cache(cpu);
			trace_kvm_guestid_change(vcpu,
						 vcpu->arch.vzguestid[cpu]);
		}

		/* Restore GuestID */
		change_c0_guestctl1(GUESTID_MASK, vcpu->arch.vzguestid[cpu]);
	} else {
		/*
		 * The Guest TLB only stores a single guest's TLB state, so
		 * flush it if another VCPU has executed on this CPU.
		 *
		 * We also flush if we've executed on another CPU, as the guest
		 * mappings may have changed without hypervisor knowledge.
		 */
		if (migrated || last_exec_vcpu[cpu] != vcpu)
			kvm_vz_local_flush_guesttlb_all();
		last_exec_vcpu[cpu] = vcpu;

		/*
		 * Root ASID dealiases guest GPA mappings in the root TLB.
		 * Allocate new root ASID if needed.
		 */
		if (cpumask_test_and_clear_cpu(cpu, &kvm->arch.asid_flush_mask))
			get_new_mmu_context(gpa_mm);
		else
			check_mmu_context(gpa_mm);
	}
}