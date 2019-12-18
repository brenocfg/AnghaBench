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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  comparecount_timer; int /*<<< orphan*/  count_hz; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int NSEC_PER_SEC ; 
 int div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int) ; 
 int kvm_read_c0_guest_compare (struct mips_coproc*) ; 

__attribute__((used)) static void kvm_mips_resume_hrtimer(struct kvm_vcpu *vcpu,
				    ktime_t now, u32 count)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	u32 compare;
	u64 delta;
	ktime_t expire;

	/* Calculate timeout (wrap 0 to 2^32) */
	compare = kvm_read_c0_guest_compare(cop0);
	delta = (u64)(u32)(compare - count - 1) + 1;
	delta = div_u64(delta * NSEC_PER_SEC, vcpu->arch.count_hz);
	expire = ktime_add_ns(now, delta);

	/* Update hrtimer to use new timeout */
	hrtimer_cancel(&vcpu->arch.comparecount_timer);
	hrtimer_start(&vcpu->arch.comparecount_timer, expire, HRTIMER_MODE_ABS);
}