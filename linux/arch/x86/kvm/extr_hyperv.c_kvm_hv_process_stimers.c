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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ enable; } ;
struct kvm_vcpu_hv_stimer {scalar_t__ exp_time; int /*<<< orphan*/  msg_pending; scalar_t__ count; TYPE_1__ config; } ;
struct kvm_vcpu_hv {struct kvm_vcpu_hv_stimer* stimer; int /*<<< orphan*/  stimer_pending_bitmap; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct kvm_vcpu_hv_stimer*) ; 
 scalar_t__ get_time_ref_counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stimer_cleanup (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  stimer_expiration (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  stimer_start (struct kvm_vcpu_hv_stimer*) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 struct kvm_vcpu_hv* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 

void kvm_hv_process_stimers(struct kvm_vcpu *vcpu)
{
	struct kvm_vcpu_hv *hv_vcpu = vcpu_to_hv_vcpu(vcpu);
	struct kvm_vcpu_hv_stimer *stimer;
	u64 time_now, exp_time;
	int i;

	for (i = 0; i < ARRAY_SIZE(hv_vcpu->stimer); i++)
		if (test_and_clear_bit(i, hv_vcpu->stimer_pending_bitmap)) {
			stimer = &hv_vcpu->stimer[i];
			if (stimer->config.enable) {
				exp_time = stimer->exp_time;

				if (exp_time) {
					time_now =
						get_time_ref_counter(vcpu->kvm);
					if (time_now >= exp_time)
						stimer_expiration(stimer);
				}

				if ((stimer->config.enable) &&
				    stimer->count) {
					if (!stimer->msg_pending)
						stimer_start(stimer);
				} else
					stimer_cleanup(stimer);
			}
		}
}