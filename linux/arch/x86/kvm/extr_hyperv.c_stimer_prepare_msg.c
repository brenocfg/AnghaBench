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
struct TYPE_4__ {int payload_size; int /*<<< orphan*/  message_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  payload; } ;
struct hv_message {TYPE_2__ header; TYPE_1__ u; } ;
struct kvm_vcpu_hv_stimer {int /*<<< orphan*/  index; struct hv_message msg; } ;
struct hv_timer_message_payload {scalar_t__ delivery_time; scalar_t__ expiration_time; int /*<<< orphan*/  timer_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVMSG_TIMER_EXPIRED ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stimer_prepare_msg(struct kvm_vcpu_hv_stimer *stimer)
{
	struct hv_message *msg = &stimer->msg;
	struct hv_timer_message_payload *payload =
			(struct hv_timer_message_payload *)&msg->u.payload;

	memset(&msg->header, 0, sizeof(msg->header));
	msg->header.message_type = HVMSG_TIMER_EXPIRED;
	msg->header.payload_size = sizeof(*payload);

	payload->timer_index = stimer->index;
	payload->expiration_time = 0;
	payload->delivery_time = 0;
}