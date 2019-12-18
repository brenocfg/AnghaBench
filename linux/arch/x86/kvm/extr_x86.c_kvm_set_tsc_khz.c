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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ virtual_tsc_khz; int /*<<< orphan*/  virtual_tsc_mult; int /*<<< orphan*/  virtual_tsc_shift; int /*<<< orphan*/  tsc_scaling_ratio; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 scalar_t__ adjust_tsc_khz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_default_tsc_scaling_ratio ; 
 int /*<<< orphan*/  kvm_get_time_scale (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int set_tsc_khz (struct kvm_vcpu*,scalar_t__,int) ; 
 int /*<<< orphan*/  tsc_khz ; 
 int /*<<< orphan*/  tsc_tolerance_ppm ; 

__attribute__((used)) static int kvm_set_tsc_khz(struct kvm_vcpu *vcpu, u32 user_tsc_khz)
{
	u32 thresh_lo, thresh_hi;
	int use_scaling = 0;

	/* tsc_khz can be zero if TSC calibration fails */
	if (user_tsc_khz == 0) {
		/* set tsc_scaling_ratio to a safe value */
		vcpu->arch.tsc_scaling_ratio = kvm_default_tsc_scaling_ratio;
		return -1;
	}

	/* Compute a scale to convert nanoseconds in TSC cycles */
	kvm_get_time_scale(user_tsc_khz * 1000LL, NSEC_PER_SEC,
			   &vcpu->arch.virtual_tsc_shift,
			   &vcpu->arch.virtual_tsc_mult);
	vcpu->arch.virtual_tsc_khz = user_tsc_khz;

	/*
	 * Compute the variation in TSC rate which is acceptable
	 * within the range of tolerance and decide if the
	 * rate being applied is within that bounds of the hardware
	 * rate.  If so, no scaling or compensation need be done.
	 */
	thresh_lo = adjust_tsc_khz(tsc_khz, -tsc_tolerance_ppm);
	thresh_hi = adjust_tsc_khz(tsc_khz, tsc_tolerance_ppm);
	if (user_tsc_khz < thresh_lo || user_tsc_khz > thresh_hi) {
		pr_debug("kvm: requested TSC rate %u falls outside tolerance [%u,%u]\n", user_tsc_khz, thresh_lo, thresh_hi);
		use_scaling = 1;
	}
	return set_tsc_khz(vcpu, user_tsc_khz, use_scaling);
}