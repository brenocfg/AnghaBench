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
struct p2p_data {scalar_t__ state; void* pending_action_state; scalar_t__ user_initiated_pd; TYPE_2__* p2ps_prov; TYPE_1__* cfg; scalar_t__ send_action_in_progress; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  session_id; int /*<<< orphan*/  adv_id; int /*<<< orphan*/  session_mac; int /*<<< orphan*/  adv_mac; int /*<<< orphan*/  pd_seeker; } ;
struct TYPE_3__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* p2ps_prov_complete ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_action_done ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ P2P_IDLE ; 
 scalar_t__ P2P_LISTEN_ONLY ; 
 void* P2P_NO_PENDING_ACTION ; 
 int /*<<< orphan*/  P2P_PD_DURING_FIND ; 
 void* P2P_PENDING_PD ; 
 scalar_t__ P2P_SC_SUCCESS_DEFERRED ; 
 scalar_t__ P2P_SEARCH ; 
 int /*<<< orphan*/  p2p_continue_find (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int /*<<< orphan*/  p2p_reset_pending_pd (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_timeout (struct p2p_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2ps_prov_free (struct p2p_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_prov_disc_cb(struct p2p_data *p2p, int success)
{
	p2p_dbg(p2p, "Provision Discovery Request TX callback: success=%d",
		success);

	/*
	 * Postpone resetting the pending action state till after we actually
	 * time out. This allows us to take some action like notifying any
	 * interested parties about no response to the request.
	 *
	 * When the timer (below) goes off we check in IDLE, SEARCH, or
	 * LISTEN_ONLY state, which are the only allowed states to issue a PD
	 * requests in, if this was still pending and then raise notification.
	 */

	if (!success) {
		p2p->pending_action_state = P2P_NO_PENDING_ACTION;

		if (p2p->user_initiated_pd &&
		    (p2p->state == P2P_SEARCH || p2p->state == P2P_LISTEN_ONLY))
		{
			/* Retry request from timeout to avoid busy loops */
			p2p->pending_action_state = P2P_PENDING_PD;
			p2p_set_timeout(p2p, 0, 50000);
		} else if (p2p->state != P2P_IDLE)
			p2p_continue_find(p2p);
		else if (p2p->user_initiated_pd) {
			p2p->pending_action_state = P2P_PENDING_PD;
			p2p_set_timeout(p2p, 0, 300000);
		}
		return;
	}

	/*
	 * If after PD Request the peer doesn't expect to receive PD Response
	 * the PD Request ACK indicates a completion of the current PD. This
	 * happens only on the advertiser side sending the follow-on PD Request
	 * with the status different than 12 (Success: accepted by user).
	 */
	if (p2p->p2ps_prov && !p2p->p2ps_prov->pd_seeker &&
	    p2p->p2ps_prov->status != P2P_SC_SUCCESS_DEFERRED) {
		p2p_dbg(p2p, "P2PS PD completion on Follow-on PD Request ACK");

		if (p2p->send_action_in_progress) {
			p2p->send_action_in_progress = 0;
			p2p->cfg->send_action_done(p2p->cfg->cb_ctx);
		}

		p2p->pending_action_state = P2P_NO_PENDING_ACTION;

		if (p2p->cfg->p2ps_prov_complete) {
			p2p->cfg->p2ps_prov_complete(
				p2p->cfg->cb_ctx,
				p2p->p2ps_prov->status,
				p2p->p2ps_prov->adv_mac,
				p2p->p2ps_prov->adv_mac,
				p2p->p2ps_prov->session_mac,
				NULL, p2p->p2ps_prov->adv_id,
				p2p->p2ps_prov->session_id,
				0, 0, NULL, 0, 0, 0,
				NULL, NULL, 0, 0, NULL, 0);
		}

		if (p2p->user_initiated_pd)
			p2p_reset_pending_pd(p2p);

		p2ps_prov_free(p2p);
		return;
	}

	/*
	 * This postponing, of resetting pending_action_state, needs to be
	 * done only for user initiated PD requests and not internal ones.
	 */
	if (p2p->user_initiated_pd)
		p2p->pending_action_state = P2P_PENDING_PD;
	else
		p2p->pending_action_state = P2P_NO_PENDING_ACTION;

	/* Wait for response from the peer */
	if (p2p->state == P2P_SEARCH)
		p2p_set_state(p2p, P2P_PD_DURING_FIND);
	p2p_set_timeout(p2p, 0, 200000);
}