#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ib_rmpp_mad {int /*<<< orphan*/  rmpp_hdr; } ;
struct ib_mad_send_wr_private {int /*<<< orphan*/  send_buf; } ;
struct ib_mad_send_wc {int /*<<< orphan*/ * send_buf; scalar_t__ vendor_err; int /*<<< orphan*/  status; } ;
struct TYPE_9__ {TYPE_1__* mad; int /*<<< orphan*/  list; } ;
struct ib_mad_recv_wc {TYPE_2__ recv_buf; int /*<<< orphan*/  rmpp_list; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* recv_handler ) (TYPE_3__*,int /*<<< orphan*/ *,struct ib_mad_recv_wc*) ;} ;
struct ib_mad_agent_private {TYPE_3__ agent; int /*<<< orphan*/  refcount; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  mgmt_class; } ;
struct TYPE_8__ {TYPE_6__ mad_hdr; } ;

/* Variables and functions */
 int IB_MGMT_RMPP_FLAG_ACTIVE ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deref_mad_agent (struct ib_mad_agent_private*) ; 
 struct ib_mad_send_wr_private* ib_find_send_mad (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 int ib_get_rmpp_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ ib_is_mad_class_rmpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mad_complete_send_wr (struct ib_mad_send_wr_private*,struct ib_mad_send_wc*) ; 
 scalar_t__ ib_mad_kernel_rmpp_agent (TYPE_3__*) ; 
 int /*<<< orphan*/  ib_mark_mad_done (struct ib_mad_send_wr_private*) ; 
 struct ib_mad_recv_wc* ib_process_rmpp_recv_wc (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 scalar_t__ ib_response_mad (TYPE_6__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ *,struct ib_mad_recv_wc*) ; 

__attribute__((used)) static void ib_mad_complete_recv(struct ib_mad_agent_private *mad_agent_priv,
				 struct ib_mad_recv_wc *mad_recv_wc)
{
	struct ib_mad_send_wr_private *mad_send_wr;
	struct ib_mad_send_wc mad_send_wc;
	unsigned long flags;

	INIT_LIST_HEAD(&mad_recv_wc->rmpp_list);
	list_add(&mad_recv_wc->recv_buf.list, &mad_recv_wc->rmpp_list);
	if (ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)) {
		mad_recv_wc = ib_process_rmpp_recv_wc(mad_agent_priv,
						      mad_recv_wc);
		if (!mad_recv_wc) {
			deref_mad_agent(mad_agent_priv);
			return;
		}
	}

	/* Complete corresponding request */
	if (ib_response_mad(&mad_recv_wc->recv_buf.mad->mad_hdr)) {
		spin_lock_irqsave(&mad_agent_priv->lock, flags);
		mad_send_wr = ib_find_send_mad(mad_agent_priv, mad_recv_wc);
		if (!mad_send_wr) {
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
			if (!ib_mad_kernel_rmpp_agent(&mad_agent_priv->agent)
			   && ib_is_mad_class_rmpp(mad_recv_wc->recv_buf.mad->mad_hdr.mgmt_class)
			   && (ib_get_rmpp_flags(&((struct ib_rmpp_mad *)mad_recv_wc->recv_buf.mad)->rmpp_hdr)
					& IB_MGMT_RMPP_FLAG_ACTIVE)) {
				/* user rmpp is in effect
				 * and this is an active RMPP MAD
				 */
				mad_agent_priv->agent.recv_handler(
						&mad_agent_priv->agent, NULL,
						mad_recv_wc);
				atomic_dec(&mad_agent_priv->refcount);
			} else {
				/* not user rmpp, revert to normal behavior and
				 * drop the mad */
				ib_free_recv_mad(mad_recv_wc);
				deref_mad_agent(mad_agent_priv);
				return;
			}
		} else {
			ib_mark_mad_done(mad_send_wr);
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

			/* Defined behavior is to complete response before request */
			mad_agent_priv->agent.recv_handler(
					&mad_agent_priv->agent,
					&mad_send_wr->send_buf,
					mad_recv_wc);
			atomic_dec(&mad_agent_priv->refcount);

			mad_send_wc.status = IB_WC_SUCCESS;
			mad_send_wc.vendor_err = 0;
			mad_send_wc.send_buf = &mad_send_wr->send_buf;
			ib_mad_complete_send_wr(mad_send_wr, &mad_send_wc);
		}
	} else {
		mad_agent_priv->agent.recv_handler(&mad_agent_priv->agent, NULL,
						   mad_recv_wc);
		deref_mad_agent(mad_agent_priv);
	}
}