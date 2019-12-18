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
struct TYPE_3__ {int direct_mode; scalar_t__ enable; int /*<<< orphan*/  periodic; } ;
struct kvm_vcpu_hv_stimer {int msg_pending; TYPE_1__ config; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int stimer_notify_direct (struct kvm_vcpu_hv_stimer*) ; 
 int stimer_send_msg (struct kvm_vcpu_hv_stimer*) ; 
 TYPE_2__* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  trace_kvm_hv_stimer_expiration (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void stimer_expiration(struct kvm_vcpu_hv_stimer *stimer)
{
	int r, direct = stimer->config.direct_mode;

	stimer->msg_pending = true;
	if (!direct)
		r = stimer_send_msg(stimer);
	else
		r = stimer_notify_direct(stimer);
	trace_kvm_hv_stimer_expiration(stimer_to_vcpu(stimer)->vcpu_id,
				       stimer->index, direct, r);
	if (!r) {
		stimer->msg_pending = false;
		if (!(stimer->config.periodic))
			stimer->config.enable = 0;
	}
}