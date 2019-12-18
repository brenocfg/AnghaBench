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
struct p2p_data {int state; int search_delay; int in_search_delay; int /*<<< orphan*/  ext_listen_only; int /*<<< orphan*/  pending_action_state; TYPE_1__* cfg; scalar_t__ drv_in_listen; scalar_t__ in_listen; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* stop_listen ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  P2P_CONNECT 140 
#define  P2P_CONNECT_LISTEN 139 
#define  P2P_GO_NEG 138 
#define  P2P_IDLE 137 
#define  P2P_INVITE 136 
#define  P2P_INVITE_LISTEN 135 
#define  P2P_LISTEN_ONLY 134 
#define  P2P_PD_DURING_FIND 133 
 int /*<<< orphan*/  P2P_PENDING_PD ; 
#define  P2P_PROVISIONING 132 
#define  P2P_SD_DURING_FIND 131 
#define  P2P_SEARCH 130 
#define  P2P_WAIT_PEER_CONNECT 129 
#define  P2P_WAIT_PEER_IDLE 128 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int /*<<< orphan*/  p2p_search (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int const) ; 
 int /*<<< orphan*/  p2p_set_timeout (struct p2p_data*,int,int) ; 
 int /*<<< orphan*/  p2p_state_txt (int) ; 
 int /*<<< orphan*/  p2p_timeout_connect (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_connect_listen (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_invite (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_invite_listen (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_prov_disc_during_find (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_prov_disc_req (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_sd_during_find (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_wait_peer_connect (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_timeout_wait_peer_idle (struct p2p_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_state_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct p2p_data *p2p = eloop_ctx;

	p2p_dbg(p2p, "Timeout (state=%s)", p2p_state_txt(p2p->state));

	p2p->in_listen = 0;
	if (p2p->drv_in_listen) {
		p2p_dbg(p2p, "Driver is still in listen state - stop it");
		p2p->cfg->stop_listen(p2p->cfg->cb_ctx);
	}

	switch (p2p->state) {
	case P2P_IDLE:
		/* Check if we timed out waiting for PD req */
		if (p2p->pending_action_state == P2P_PENDING_PD)
			p2p_timeout_prov_disc_req(p2p);
		break;
	case P2P_SEARCH:
		/* Check if we timed out waiting for PD req */
		if (p2p->pending_action_state == P2P_PENDING_PD)
			p2p_timeout_prov_disc_req(p2p);
		if (p2p->search_delay && !p2p->in_search_delay) {
			p2p_dbg(p2p, "Delay search operation by %u ms",
				p2p->search_delay);
			p2p->in_search_delay = 1;
			p2p_set_timeout(p2p, p2p->search_delay / 1000,
					(p2p->search_delay % 1000) * 1000);
			break;
		}
		p2p->in_search_delay = 0;
		p2p_search(p2p);
		break;
	case P2P_CONNECT:
		p2p_timeout_connect(p2p);
		break;
	case P2P_CONNECT_LISTEN:
		p2p_timeout_connect_listen(p2p);
		break;
	case P2P_GO_NEG:
		break;
	case P2P_LISTEN_ONLY:
		/* Check if we timed out waiting for PD req */
		if (p2p->pending_action_state == P2P_PENDING_PD)
			p2p_timeout_prov_disc_req(p2p);

		if (p2p->ext_listen_only) {
			p2p_dbg(p2p, "Extended Listen Timing - Listen State completed");
			p2p->ext_listen_only = 0;
			p2p_set_state(p2p, P2P_IDLE);
		}
		break;
	case P2P_WAIT_PEER_CONNECT:
		p2p_timeout_wait_peer_connect(p2p);
		break;
	case P2P_WAIT_PEER_IDLE:
		p2p_timeout_wait_peer_idle(p2p);
		break;
	case P2P_SD_DURING_FIND:
		p2p_timeout_sd_during_find(p2p);
		break;
	case P2P_PROVISIONING:
		break;
	case P2P_PD_DURING_FIND:
		p2p_timeout_prov_disc_during_find(p2p);
		break;
	case P2P_INVITE:
		p2p_timeout_invite(p2p);
		break;
	case P2P_INVITE_LISTEN:
		p2p_timeout_invite_listen(p2p);
		break;
	}
}