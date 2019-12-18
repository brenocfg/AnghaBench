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
struct TYPE_2__ {int /*<<< orphan*/  count_period; int /*<<< orphan*/  comparecount_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_RESTART ; 
 int /*<<< orphan*/  hrtimer_add_expires_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum hrtimer_restart kvm_mips_count_timeout(struct kvm_vcpu *vcpu)
{
	/* Add the Count period to the current expiry time */
	hrtimer_add_expires_ns(&vcpu->arch.comparecount_timer,
			       vcpu->arch.count_period);
	return HRTIMER_RESTART;
}