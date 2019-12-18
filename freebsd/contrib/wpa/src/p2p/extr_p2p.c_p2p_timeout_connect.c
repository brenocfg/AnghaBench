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
struct p2p_data {TYPE_2__* go_neg_peer; TYPE_1__* cfg; } ;
struct TYPE_4__ {int flags; int connect_reqs; scalar_t__ oob_go_neg_freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* send_action_done ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_CONNECT_LISTEN ; 
 int P2P_DEV_PEER_WAITING_RESPONSE ; 
 int P2P_DEV_WAIT_GO_NEG_CONFIRM ; 
 int /*<<< orphan*/  p2p_connect_send (struct p2p_data*,TYPE_2__*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_go_neg_failed (struct p2p_data*,int) ; 
 int /*<<< orphan*/  p2p_listen_in_find (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_timeout (struct p2p_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_timeout_connect(struct p2p_data *p2p)
{
	p2p->cfg->send_action_done(p2p->cfg->cb_ctx);
	if (p2p->go_neg_peer &&
	    (p2p->go_neg_peer->flags & P2P_DEV_WAIT_GO_NEG_CONFIRM)) {
		p2p_dbg(p2p, "Wait for GO Negotiation Confirm timed out - assume GO Negotiation failed");
		p2p_go_neg_failed(p2p, -1);
		return;
	}
	if (p2p->go_neg_peer &&
	    (p2p->go_neg_peer->flags & P2P_DEV_PEER_WAITING_RESPONSE) &&
	    p2p->go_neg_peer->connect_reqs < 120) {
		p2p_dbg(p2p, "Peer expected to wait our response - skip listen");
		p2p_connect_send(p2p, p2p->go_neg_peer);
		return;
	}
	if (p2p->go_neg_peer && p2p->go_neg_peer->oob_go_neg_freq > 0) {
		p2p_dbg(p2p, "Skip connect-listen since GO Neg channel known (OOB)");
		p2p_set_state(p2p, P2P_CONNECT_LISTEN);
		p2p_set_timeout(p2p, 0, 30000);
		return;
	}
	p2p_set_state(p2p, P2P_CONNECT_LISTEN);
	p2p_listen_in_find(p2p, 0);
}