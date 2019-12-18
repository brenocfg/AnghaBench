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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  comparecount_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  kvm_mips_read_count_running (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

ktime_t kvm_mips_freeze_hrtimer(struct kvm_vcpu *vcpu, u32 *count)
{
	ktime_t now;

	/* stop hrtimer before finding time */
	hrtimer_cancel(&vcpu->arch.comparecount_timer);
	now = ktime_get();

	/* find count at this point and handle pending hrtimer */
	*count = kvm_mips_read_count_running(vcpu, now);

	return now;
}