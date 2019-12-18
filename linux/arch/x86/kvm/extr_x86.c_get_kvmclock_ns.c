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
typedef  scalar_t__ u64 ;
struct pvclock_vcpu_time_info {int /*<<< orphan*/  tsc_to_system_mul; int /*<<< orphan*/  tsc_shift; scalar_t__ system_time; int /*<<< orphan*/  tsc_timestamp; } ;
struct kvm_arch {scalar_t__ kvmclock_offset; int /*<<< orphan*/  pvclock_gtod_sync_lock; scalar_t__ master_kernel_ns; int /*<<< orphan*/  master_cycle_now; int /*<<< orphan*/  use_master_clock; } ;
struct kvm {struct kvm_arch arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 scalar_t__ __pvclock_read_cycles (struct pvclock_vcpu_time_info*,int /*<<< orphan*/ ) ; 
 long long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_tsc_khz ; 
 int /*<<< orphan*/  get_cpu () ; 
 scalar_t__ ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  kvm_get_time_scale (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

u64 get_kvmclock_ns(struct kvm *kvm)
{
	struct kvm_arch *ka = &kvm->arch;
	struct pvclock_vcpu_time_info hv_clock;
	u64 ret;

	spin_lock(&ka->pvclock_gtod_sync_lock);
	if (!ka->use_master_clock) {
		spin_unlock(&ka->pvclock_gtod_sync_lock);
		return ktime_get_boottime_ns() + ka->kvmclock_offset;
	}

	hv_clock.tsc_timestamp = ka->master_cycle_now;
	hv_clock.system_time = ka->master_kernel_ns + ka->kvmclock_offset;
	spin_unlock(&ka->pvclock_gtod_sync_lock);

	/* both __this_cpu_read() and rdtsc() should be on the same cpu */
	get_cpu();

	if (__this_cpu_read(cpu_tsc_khz)) {
		kvm_get_time_scale(NSEC_PER_SEC, __this_cpu_read(cpu_tsc_khz) * 1000LL,
				   &hv_clock.tsc_shift,
				   &hv_clock.tsc_to_system_mul);
		ret = __pvclock_read_cycles(&hv_clock, rdtsc());
	} else
		ret = ktime_get_boottime_ns() + ka->kvmclock_offset;

	put_cpu();

	return ret;
}