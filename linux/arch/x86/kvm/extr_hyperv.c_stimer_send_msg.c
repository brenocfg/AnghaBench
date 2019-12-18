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
struct TYPE_4__ {int periodic; int /*<<< orphan*/  sintx; } ;
struct TYPE_3__ {int /*<<< orphan*/  payload; } ;
struct hv_message {TYPE_1__ u; } ;
struct kvm_vcpu_hv_stimer {TYPE_2__ config; int /*<<< orphan*/  exp_time; struct hv_message msg; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct hv_timer_message_payload {int /*<<< orphan*/  delivery_time; int /*<<< orphan*/  expiration_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_time_ref_counter (int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int synic_deliver_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hv_message*,int) ; 
 int /*<<< orphan*/  vcpu_to_synic (struct kvm_vcpu*) ; 

__attribute__((used)) static int stimer_send_msg(struct kvm_vcpu_hv_stimer *stimer)
{
	struct kvm_vcpu *vcpu = stimer_to_vcpu(stimer);
	struct hv_message *msg = &stimer->msg;
	struct hv_timer_message_payload *payload =
			(struct hv_timer_message_payload *)&msg->u.payload;

	/*
	 * To avoid piling up periodic ticks, don't retry message
	 * delivery for them (within "lazy" lost ticks policy).
	 */
	bool no_retry = stimer->config.periodic;

	payload->expiration_time = stimer->exp_time;
	payload->delivery_time = get_time_ref_counter(vcpu->kvm);
	return synic_deliver_msg(vcpu_to_synic(vcpu),
				 stimer->config.sintx, msg,
				 no_retry);
}