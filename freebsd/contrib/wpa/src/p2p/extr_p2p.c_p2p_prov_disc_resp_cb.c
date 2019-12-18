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
struct p2p_data {TYPE_1__* cfg; int /*<<< orphan*/  pending_action_state; scalar_t__ send_action_in_progress; } ;
struct TYPE_2__ {int (* prov_disc_resp_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* send_action_done ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_NO_PENDING_ACTION ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_prov_disc_resp_cb(struct p2p_data *p2p, int success)
{
	p2p_dbg(p2p, "Provision Discovery Response TX callback: success=%d",
		success);

	if (p2p->send_action_in_progress) {
		p2p->send_action_in_progress = 0;
		p2p->cfg->send_action_done(p2p->cfg->cb_ctx);
	}

	p2p->pending_action_state = P2P_NO_PENDING_ACTION;

	if (!success)
		return;

	if (!p2p->cfg->prov_disc_resp_cb ||
	    p2p->cfg->prov_disc_resp_cb(p2p->cfg->cb_ctx) < 1)
		return;

	p2p_dbg(p2p,
		"Post-Provision Discovery operations started - do not try to continue other P2P operations");
}