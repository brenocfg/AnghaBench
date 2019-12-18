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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int count_bias; int /*<<< orphan*/  count_hz; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,int) ; 
 int kvm_mips_ktime_to_count (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mips_resume_hrtimer (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 

int kvm_mips_restore_hrtimer(struct kvm_vcpu *vcpu, ktime_t before,
			     u32 count, int min_drift)
{
	ktime_t now, count_time;
	u32 now_count, before_count;
	u64 delta;
	int drift, ret = 0;

	/* Calculate expected count at before */
	before_count = vcpu->arch.count_bias +
			kvm_mips_ktime_to_count(vcpu, before);

	/*
	 * Detect significantly negative drift, where count is lower than
	 * expected. Some negative drift is expected when hardware counter is
	 * set after kvm_mips_freeze_timer(), and it is harmless to allow the
	 * time to jump forwards a little, within reason. If the drift is too
	 * significant, adjust the bias to avoid a big Guest.CP0_Count jump.
	 */
	drift = count - before_count;
	if (drift < min_drift) {
		count_time = before;
		vcpu->arch.count_bias += drift;
		ret = drift;
		goto resume;
	}

	/* Calculate expected count right now */
	now = ktime_get();
	now_count = vcpu->arch.count_bias + kvm_mips_ktime_to_count(vcpu, now);

	/*
	 * Detect positive drift, where count is higher than expected, and
	 * adjust the bias to avoid guest time going backwards.
	 */
	drift = count - now_count;
	if (drift > 0) {
		count_time = now;
		vcpu->arch.count_bias += drift;
		ret = drift;
		goto resume;
	}

	/* Subtract nanosecond delta to find ktime when count was read */
	delta = (u64)(u32)(now_count - count);
	delta = div_u64(delta * NSEC_PER_SEC, vcpu->arch.count_hz);
	count_time = ktime_sub_ns(now, delta);

resume:
	/* Resume using the calculated ktime */
	kvm_mips_resume_hrtimer(vcpu, count_time, count);
	return ret;
}