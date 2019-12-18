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
typedef  scalar_t__ u64 ;
struct msr_data {scalar_t__ data; scalar_t__ host_initiated; } ;
struct TYPE_3__ {int virtual_tsc_khz; scalar_t__ this_tsc_generation; scalar_t__ this_tsc_write; scalar_t__ this_tsc_nsec; scalar_t__ last_guest_tsc; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct TYPE_4__ {scalar_t__ last_tsc_nsec; scalar_t__ last_tsc_write; long long last_tsc_khz; scalar_t__ cur_tsc_offset; scalar_t__ cur_tsc_generation; int /*<<< orphan*/  pvclock_gtod_sync_lock; scalar_t__ nr_vcpus_matched_tsc; int /*<<< orphan*/  tsc_write_lock; scalar_t__ cur_tsc_write; scalar_t__ cur_tsc_nsec; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_TSC_ADJUST ; 
 scalar_t__ guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  kvm_check_tsc_unstable () ; 
 scalar_t__ kvm_compute_tsc_offset (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  kvm_track_tsc_matching (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_write_tsc_offset (struct kvm_vcpu*,scalar_t__) ; 
 scalar_t__ nsec_to_cycles (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_ia32_tsc_adjust_msr (struct kvm_vcpu*,scalar_t__) ; 

void kvm_write_tsc(struct kvm_vcpu *vcpu, struct msr_data *msr)
{
	struct kvm *kvm = vcpu->kvm;
	u64 offset, ns, elapsed;
	unsigned long flags;
	bool matched;
	bool already_matched;
	u64 data = msr->data;
	bool synchronizing = false;

	raw_spin_lock_irqsave(&kvm->arch.tsc_write_lock, flags);
	offset = kvm_compute_tsc_offset(vcpu, data);
	ns = ktime_get_boottime_ns();
	elapsed = ns - kvm->arch.last_tsc_nsec;

	if (vcpu->arch.virtual_tsc_khz) {
		if (data == 0 && msr->host_initiated) {
			/*
			 * detection of vcpu initialization -- need to sync
			 * with other vCPUs. This particularly helps to keep
			 * kvm_clock stable after CPU hotplug
			 */
			synchronizing = true;
		} else {
			u64 tsc_exp = kvm->arch.last_tsc_write +
						nsec_to_cycles(vcpu, elapsed);
			u64 tsc_hz = vcpu->arch.virtual_tsc_khz * 1000LL;
			/*
			 * Special case: TSC write with a small delta (1 second)
			 * of virtual cycle time against real time is
			 * interpreted as an attempt to synchronize the CPU.
			 */
			synchronizing = data < tsc_exp + tsc_hz &&
					data + tsc_hz > tsc_exp;
		}
	}

	/*
	 * For a reliable TSC, we can match TSC offsets, and for an unstable
	 * TSC, we add elapsed time in this computation.  We could let the
	 * compensation code attempt to catch up if we fall behind, but
	 * it's better to try to match offsets from the beginning.
         */
	if (synchronizing &&
	    vcpu->arch.virtual_tsc_khz == kvm->arch.last_tsc_khz) {
		if (!kvm_check_tsc_unstable()) {
			offset = kvm->arch.cur_tsc_offset;
		} else {
			u64 delta = nsec_to_cycles(vcpu, elapsed);
			data += delta;
			offset = kvm_compute_tsc_offset(vcpu, data);
		}
		matched = true;
		already_matched = (vcpu->arch.this_tsc_generation == kvm->arch.cur_tsc_generation);
	} else {
		/*
		 * We split periods of matched TSC writes into generations.
		 * For each generation, we track the original measured
		 * nanosecond time, offset, and write, so if TSCs are in
		 * sync, we can match exact offset, and if not, we can match
		 * exact software computation in compute_guest_tsc()
		 *
		 * These values are tracked in kvm->arch.cur_xxx variables.
		 */
		kvm->arch.cur_tsc_generation++;
		kvm->arch.cur_tsc_nsec = ns;
		kvm->arch.cur_tsc_write = data;
		kvm->arch.cur_tsc_offset = offset;
		matched = false;
	}

	/*
	 * We also track th most recent recorded KHZ, write and time to
	 * allow the matching interval to be extended at each write.
	 */
	kvm->arch.last_tsc_nsec = ns;
	kvm->arch.last_tsc_write = data;
	kvm->arch.last_tsc_khz = vcpu->arch.virtual_tsc_khz;

	vcpu->arch.last_guest_tsc = data;

	/* Keep track of which generation this VCPU has synchronized to */
	vcpu->arch.this_tsc_generation = kvm->arch.cur_tsc_generation;
	vcpu->arch.this_tsc_nsec = kvm->arch.cur_tsc_nsec;
	vcpu->arch.this_tsc_write = kvm->arch.cur_tsc_write;

	if (!msr->host_initiated && guest_cpuid_has(vcpu, X86_FEATURE_TSC_ADJUST))
		update_ia32_tsc_adjust_msr(vcpu, offset);

	kvm_vcpu_write_tsc_offset(vcpu, offset);
	raw_spin_unlock_irqrestore(&kvm->arch.tsc_write_lock, flags);

	spin_lock(&kvm->arch.pvclock_gtod_sync_lock);
	if (!matched) {
		kvm->arch.nr_vcpus_matched_tsc = 0;
	} else if (!already_matched) {
		kvm->arch.nr_vcpus_matched_tsc++;
	}

	kvm_track_tsc_matching(vcpu);
	spin_unlock(&kvm->arch.pvclock_gtod_sync_lock);
}