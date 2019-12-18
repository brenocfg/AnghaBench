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
struct p2p_data {TYPE_1__* invite_peer; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_DEV_WAIT_INV_REQ_ACK ; 
 int /*<<< orphan*/  P2P_INVITE ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_timeout (struct p2p_data*,int /*<<< orphan*/ ,int) ; 

void p2p_invitation_req_cb(struct p2p_data *p2p, int success)
{
	p2p_dbg(p2p, "Invitation Request TX callback: success=%d", success);

	if (p2p->invite_peer == NULL) {
		p2p_dbg(p2p, "No pending Invite");
		return;
	}

	if (success)
		p2p->invite_peer->flags &= ~P2P_DEV_WAIT_INV_REQ_ACK;

	/*
	 * Use P2P find, if needed, to find the other device from its listen
	 * channel.
	 */
	p2p_set_state(p2p, P2P_INVITE);
	p2p_set_timeout(p2p, 0, success ? 500000 : 100000);
}