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
struct p2p_go_neg_results {int status; int /*<<< orphan*/  peer_interface_addr; int /*<<< orphan*/  peer_device_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  p2p_device_addr; } ;
struct p2p_device {int /*<<< orphan*/  intended_addr; TYPE_1__ info; int /*<<< orphan*/ * go_neg_conf; scalar_t__ oob_pw_id; int /*<<< orphan*/  wps_method; int /*<<< orphan*/  flags; } ;
struct p2p_data {scalar_t__ state; TYPE_2__* cfg; struct p2p_device* go_neg_peer; } ;
typedef  int /*<<< orphan*/  res ;
struct TYPE_4__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* go_neg_completed ) (int /*<<< orphan*/ ,struct p2p_go_neg_results*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  P2P_DEV_PEER_WAITING_RESPONSE ; 
 int /*<<< orphan*/  P2P_IDLE ; 
 scalar_t__ P2P_SEARCH ; 
 int /*<<< orphan*/  WPS_NOT_READY ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct p2p_go_neg_results*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_clear_timeout (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_go_neg_wait_timeout ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct p2p_go_neg_results*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void p2p_go_neg_failed(struct p2p_data *p2p, int status)
{
	struct p2p_go_neg_results res;
	struct p2p_device *peer = p2p->go_neg_peer;

	if (!peer)
		return;

	eloop_cancel_timeout(p2p_go_neg_wait_timeout, p2p, NULL);
	if (p2p->state != P2P_SEARCH) {
		/*
		 * Clear timeouts related to GO Negotiation if no new p2p_find
		 * has been started.
		 */
		p2p_clear_timeout(p2p);
		p2p_set_state(p2p, P2P_IDLE);
	}

	peer->flags &= ~P2P_DEV_PEER_WAITING_RESPONSE;
	peer->wps_method = WPS_NOT_READY;
	peer->oob_pw_id = 0;
	wpabuf_free(peer->go_neg_conf);
	peer->go_neg_conf = NULL;
	p2p->go_neg_peer = NULL;

	os_memset(&res, 0, sizeof(res));
	res.status = status;
	os_memcpy(res.peer_device_addr, peer->info.p2p_device_addr, ETH_ALEN);
	os_memcpy(res.peer_interface_addr, peer->intended_addr, ETH_ALEN);
	p2p->cfg->go_neg_completed(p2p->cfg->cb_ctx, &res);
}