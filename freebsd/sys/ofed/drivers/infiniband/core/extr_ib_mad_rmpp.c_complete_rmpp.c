#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mad_rmpp_recv {int seg_num; int /*<<< orphan*/  cleanup_work; TYPE_1__* agent; struct ib_mad_recv_wc* rmpp_wc; int /*<<< orphan*/  timeout_work; } ;
struct ib_mad_recv_wc {int /*<<< orphan*/  mad_len; } ;
struct TYPE_6__ {TYPE_2__* port_priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  wq; } ;
struct TYPE_4__ {TYPE_3__* qp_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_recv (struct mad_rmpp_recv*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mad_len (struct mad_rmpp_recv*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_mad_recv_wc * complete_rmpp(struct mad_rmpp_recv *rmpp_recv)
{
	struct ib_mad_recv_wc *rmpp_wc;

	ack_recv(rmpp_recv, rmpp_recv->rmpp_wc);
	if (rmpp_recv->seg_num > 1)
		cancel_delayed_work(&rmpp_recv->timeout_work);

	rmpp_wc = rmpp_recv->rmpp_wc;
	rmpp_wc->mad_len = get_mad_len(rmpp_recv);
	/* 10 seconds until we can find the packet lifetime */
	queue_delayed_work(rmpp_recv->agent->qp_info->port_priv->wq,
			   &rmpp_recv->cleanup_work, msecs_to_jiffies(10000));
	return rmpp_wc;
}