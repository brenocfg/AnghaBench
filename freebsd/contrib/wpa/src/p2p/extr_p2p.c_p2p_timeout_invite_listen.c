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
struct p2p_data {TYPE_3__* invite_peer; TYPE_1__* cfg; int /*<<< orphan*/  invite_dev_pw_id; int /*<<< orphan*/  invite_go_dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  p2p_device_addr; } ;
struct TYPE_6__ {int invitation_reqs; TYPE_2__ info; } ;
struct TYPE_4__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* invitation_result ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_IDLE ; 
 int /*<<< orphan*/  P2P_INVITE ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_invite_send (struct p2p_data*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_timeout_invite_listen(struct p2p_data *p2p)
{
	if (p2p->invite_peer && p2p->invite_peer->invitation_reqs < 100) {
		p2p_set_state(p2p, P2P_INVITE);
		p2p_invite_send(p2p, p2p->invite_peer,
				p2p->invite_go_dev_addr, p2p->invite_dev_pw_id);
	} else {
		if (p2p->invite_peer) {
			p2p_dbg(p2p, "Invitation Request retry limit reached");
			if (p2p->cfg->invitation_result)
				p2p->cfg->invitation_result(
					p2p->cfg->cb_ctx, -1, NULL, NULL,
					p2p->invite_peer->info.p2p_device_addr,
					0, 0);
		}
		p2p_set_state(p2p, P2P_IDLE);
	}
}