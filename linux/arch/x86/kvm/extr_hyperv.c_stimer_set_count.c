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
struct TYPE_3__ {int enable; scalar_t__ auto_enable; } ;
struct kvm_vcpu_hv_stimer {scalar_t__ count; TYPE_1__ config; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  stimer_cleanup (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  stimer_mark_pending (struct kvm_vcpu_hv_stimer*,int) ; 
 TYPE_2__* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  trace_kvm_hv_stimer_set_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int stimer_set_count(struct kvm_vcpu_hv_stimer *stimer, u64 count,
			    bool host)
{
	trace_kvm_hv_stimer_set_count(stimer_to_vcpu(stimer)->vcpu_id,
				      stimer->index, count, host);

	stimer_cleanup(stimer);
	stimer->count = count;
	if (stimer->count == 0)
		stimer->config.enable = 0;
	else if (stimer->config.auto_enable)
		stimer->config.enable = 1;

	if (stimer->config.enable)
		stimer_mark_pending(stimer, false);

	return 0;
}