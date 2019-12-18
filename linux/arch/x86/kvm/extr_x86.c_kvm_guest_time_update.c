#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct TYPE_5__ {int /*<<< orphan*/  flags; scalar_t__ system_time; scalar_t__ tsc_timestamp; int /*<<< orphan*/  tsc_to_system_mul; int /*<<< orphan*/  tsc_shift; } ;
struct kvm_vcpu_arch {unsigned long hw_tsc_khz; TYPE_2__ hv_clock; scalar_t__ pv_time_enabled; scalar_t__ last_guest_tsc; scalar_t__ tsc_catchup; } ;
struct kvm_vcpu {TYPE_1__* kvm; struct kvm_vcpu_arch arch; } ;
struct kvm_arch {int use_master_clock; scalar_t__ master_cycle_now; scalar_t__ kvmclock_offset; int /*<<< orphan*/  pvclock_gtod_sync_lock; scalar_t__ master_kernel_ns; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {struct kvm_arch arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_CLOCK_UPDATE ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  PVCLOCK_TSC_STABLE_BIT ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_tsc_offset_guest (struct kvm_vcpu*,scalar_t__) ; 
 scalar_t__ compute_guest_tsc (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_tsc_khz ; 
 scalar_t__ ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  kvm_get_time_scale (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kvm_vcpu* kvm_get_vcpu (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_has_tsc_control ; 
 int /*<<< orphan*/  kvm_hv_setup_tsc_page (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ kvm_read_l1_tsc (struct kvm_vcpu*,scalar_t__) ; 
 unsigned long kvm_scale_tsc (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  kvm_setup_pvclock_page (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ rdtsc () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int kvm_guest_time_update(struct kvm_vcpu *v)
{
	unsigned long flags, tgt_tsc_khz;
	struct kvm_vcpu_arch *vcpu = &v->arch;
	struct kvm_arch *ka = &v->kvm->arch;
	s64 kernel_ns;
	u64 tsc_timestamp, host_tsc;
	u8 pvclock_flags;
	bool use_master_clock;

	kernel_ns = 0;
	host_tsc = 0;

	/*
	 * If the host uses TSC clock, then passthrough TSC as stable
	 * to the guest.
	 */
	spin_lock(&ka->pvclock_gtod_sync_lock);
	use_master_clock = ka->use_master_clock;
	if (use_master_clock) {
		host_tsc = ka->master_cycle_now;
		kernel_ns = ka->master_kernel_ns;
	}
	spin_unlock(&ka->pvclock_gtod_sync_lock);

	/* Keep irq disabled to prevent changes to the clock */
	local_irq_save(flags);
	tgt_tsc_khz = __this_cpu_read(cpu_tsc_khz);
	if (unlikely(tgt_tsc_khz == 0)) {
		local_irq_restore(flags);
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, v);
		return 1;
	}
	if (!use_master_clock) {
		host_tsc = rdtsc();
		kernel_ns = ktime_get_boottime_ns();
	}

	tsc_timestamp = kvm_read_l1_tsc(v, host_tsc);

	/*
	 * We may have to catch up the TSC to match elapsed wall clock
	 * time for two reasons, even if kvmclock is used.
	 *   1) CPU could have been running below the maximum TSC rate
	 *   2) Broken TSC compensation resets the base at each VCPU
	 *      entry to avoid unknown leaps of TSC even when running
	 *      again on the same CPU.  This may cause apparent elapsed
	 *      time to disappear, and the guest to stand still or run
	 *	very slowly.
	 */
	if (vcpu->tsc_catchup) {
		u64 tsc = compute_guest_tsc(v, kernel_ns);
		if (tsc > tsc_timestamp) {
			adjust_tsc_offset_guest(v, tsc - tsc_timestamp);
			tsc_timestamp = tsc;
		}
	}

	local_irq_restore(flags);

	/* With all the info we got, fill in the values */

	if (kvm_has_tsc_control)
		tgt_tsc_khz = kvm_scale_tsc(v, tgt_tsc_khz);

	if (unlikely(vcpu->hw_tsc_khz != tgt_tsc_khz)) {
		kvm_get_time_scale(NSEC_PER_SEC, tgt_tsc_khz * 1000LL,
				   &vcpu->hv_clock.tsc_shift,
				   &vcpu->hv_clock.tsc_to_system_mul);
		vcpu->hw_tsc_khz = tgt_tsc_khz;
	}

	vcpu->hv_clock.tsc_timestamp = tsc_timestamp;
	vcpu->hv_clock.system_time = kernel_ns + v->kvm->arch.kvmclock_offset;
	vcpu->last_guest_tsc = tsc_timestamp;

	/* If the host uses TSC clocksource, then it is stable */
	pvclock_flags = 0;
	if (use_master_clock)
		pvclock_flags |= PVCLOCK_TSC_STABLE_BIT;

	vcpu->hv_clock.flags = pvclock_flags;

	if (vcpu->pv_time_enabled)
		kvm_setup_pvclock_page(v);
	if (v == kvm_get_vcpu(v->kvm, 0))
		kvm_hv_setup_tsc_page(v->kvm, &vcpu->hv_clock);
	return 0;
}