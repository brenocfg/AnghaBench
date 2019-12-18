#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rdma_cm_id {scalar_t__ qp_type; int /*<<< orphan*/ * recv_cq_channel; int /*<<< orphan*/ * send_cq_channel; int /*<<< orphan*/ * recv_cq; int /*<<< orphan*/ * send_cq; scalar_t__ srq; } ;

/* Variables and functions */
 scalar_t__ IBV_QPT_XRC_RECV ; 
 int /*<<< orphan*/  ibv_destroy_comp_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibv_destroy_cq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucma_destroy_cqs(struct rdma_cm_id *id)
{
	if (id->qp_type == IBV_QPT_XRC_RECV && id->srq)
		return;

	if (id->recv_cq) {
		ibv_destroy_cq(id->recv_cq);
		if (id->send_cq && (id->send_cq != id->recv_cq)) {
			ibv_destroy_cq(id->send_cq);
			id->send_cq = NULL;
		}
		id->recv_cq = NULL;
	}

	if (id->recv_cq_channel) {
		ibv_destroy_comp_channel(id->recv_cq_channel);
		if (id->send_cq_channel && (id->send_cq_channel != id->recv_cq_channel)) {
			ibv_destroy_comp_channel(id->send_cq_channel);
			id->send_cq_channel = NULL;
		}
		id->recv_cq_channel = NULL;
	}
}