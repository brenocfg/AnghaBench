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
typedef  int uint32_t ;
struct ntb_transport_qp {int client_ready; int /*<<< orphan*/  link_work; scalar_t__ link_is_up; int /*<<< orphan*/  dev; struct ntb_transport_ctx* transport; } ;
struct ntb_transport_ctx {int qp_count; TYPE_1__* qp_vec; } ;
struct TYPE_2__ {scalar_t__ client_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTBT_QP_LINKS ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_peer_spad_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntb_send_link_down (struct ntb_transport_qp*) ; 

void
ntb_transport_link_down(struct ntb_transport_qp *qp)
{
	struct ntb_transport_ctx *nt = qp->transport;
	int i;
	uint32_t val;

	qp->client_ready = false;
	for (i = 0, val = 0; i < nt->qp_count; i++) {
		if (nt->qp_vec[i].client_ready)
			val |= (1 << i);
	}
	ntb_peer_spad_write(qp->dev, NTBT_QP_LINKS, val);

	if (qp->link_is_up)
		ntb_send_link_down(qp);
	else
		callout_drain(&qp->link_work);
}