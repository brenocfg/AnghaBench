#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
struct ib_umad_packet {TYPE_2__ mad; int /*<<< orphan*/  length; TYPE_4__* msg; } ;
struct ib_umad_file {int dummy; } ;
struct ib_mad_send_wc {scalar_t__ status; TYPE_3__* send_buf; } ;
struct ib_mad_agent {struct ib_umad_file* context; } ;
struct TYPE_8__ {int /*<<< orphan*/  ah; } ;
struct TYPE_7__ {struct ib_umad_packet** context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  IB_MGMT_MAD_HDR ; 
 scalar_t__ IB_WC_RESP_TIMEOUT_ERR ; 
 int /*<<< orphan*/  dequeue_send (struct ib_umad_file*,struct ib_umad_packet*) ; 
 int /*<<< orphan*/  ib_destroy_ah (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_free_send_mad (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct ib_umad_packet*) ; 
 int /*<<< orphan*/  queue_packet (struct ib_umad_file*,struct ib_mad_agent*,struct ib_umad_packet*) ; 

__attribute__((used)) static void send_handler(struct ib_mad_agent *agent,
			 struct ib_mad_send_wc *send_wc)
{
	struct ib_umad_file *file = agent->context;
	struct ib_umad_packet *packet = send_wc->send_buf->context[0];

	dequeue_send(file, packet);
	ib_destroy_ah(packet->msg->ah);
	ib_free_send_mad(packet->msg);

	if (send_wc->status == IB_WC_RESP_TIMEOUT_ERR) {
		packet->length = IB_MGMT_MAD_HDR;
		packet->mad.hdr.status = ETIMEDOUT;
		if (!queue_packet(file, agent, packet))
			return;
	}
	kfree(packet);
}