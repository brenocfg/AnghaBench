#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct p2p_device {int dummy; } ;
struct p2p_data {struct p2p_device* go_neg_peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_WAIT_PEER_CONNECT ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_listen_in_find (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_timeout_wait_peer_idle(struct p2p_data *p2p)
{
	struct p2p_device *dev = p2p->go_neg_peer;

	if (dev == NULL) {
		p2p_dbg(p2p, "Unknown GO Neg peer - stop GO Neg wait");
		return;
	}

	p2p_dbg(p2p, "Go to Listen state while waiting for the peer to become ready for GO Negotiation");
	p2p_set_state(p2p, P2P_WAIT_PEER_CONNECT);
	p2p_listen_in_find(p2p, 0);
}