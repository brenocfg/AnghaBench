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
struct ntb_transport_qp {int client_ready; int /*<<< orphan*/  link_work; int /*<<< orphan*/  qp_num; struct ntb_transport_ctx* transport; } ;
struct ntb_transport_ctx {scalar_t__ link_is_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  ntb_printf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_qp_link_work ; 

void
ntb_transport_link_up(struct ntb_transport_qp *qp)
{
	struct ntb_transport_ctx *nt = qp->transport;

	qp->client_ready = true;

	ntb_printf(2, "qp %d client ready\n", qp->qp_num);

	if (nt->link_is_up)
		callout_reset(&qp->link_work, 0, ntb_qp_link_work, qp);
}