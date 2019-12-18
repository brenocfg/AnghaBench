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
struct p2p_data {scalar_t__ state; scalar_t__ send_action_in_progress; int /*<<< orphan*/ * invite_peer; int /*<<< orphan*/ * sd_peer; TYPE_2__* go_neg_peer; int /*<<< orphan*/  start_after_scan; scalar_t__ p2ps_seek_count; TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* find_stopped ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_AFTER_SCAN_NOTHING ; 
 int /*<<< orphan*/  P2P_DEV_PEER_WAITING_RESPONSE ; 
 int /*<<< orphan*/  P2P_IDLE ; 
 scalar_t__ P2P_SD_DURING_FIND ; 
 scalar_t__ P2P_SEARCH ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_clear_timeout (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_find_timeout ; 
 int /*<<< orphan*/  p2p_free_req_dev_types (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_stop_listen_for_freq (struct p2p_data*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void p2p_stop_find_for_freq(struct p2p_data *p2p, int freq)
{
	p2p_dbg(p2p, "Stopping find");
	eloop_cancel_timeout(p2p_find_timeout, p2p, NULL);
	p2p_clear_timeout(p2p);
	if (p2p->state == P2P_SEARCH || p2p->state == P2P_SD_DURING_FIND)
		p2p->cfg->find_stopped(p2p->cfg->cb_ctx);

	p2p->p2ps_seek_count = 0;

	p2p_set_state(p2p, P2P_IDLE);
	p2p_free_req_dev_types(p2p);
	p2p->start_after_scan = P2P_AFTER_SCAN_NOTHING;
	if (p2p->go_neg_peer)
		p2p->go_neg_peer->flags &= ~P2P_DEV_PEER_WAITING_RESPONSE;
	p2p->go_neg_peer = NULL;
	p2p->sd_peer = NULL;
	p2p->invite_peer = NULL;
	p2p_stop_listen_for_freq(p2p, freq);
	p2p->send_action_in_progress = 0;
}