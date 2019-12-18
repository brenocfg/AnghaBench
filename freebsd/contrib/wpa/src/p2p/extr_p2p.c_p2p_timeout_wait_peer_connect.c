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
struct p2p_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_ctx; scalar_t__ (* is_concurrent_session_active ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_WAIT_PEER_IDLE ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_timeout (struct p2p_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_timeout_wait_peer_connect(struct p2p_data *p2p)
{
	p2p_set_state(p2p, P2P_WAIT_PEER_IDLE);

	if (p2p->cfg->is_concurrent_session_active &&
	    p2p->cfg->is_concurrent_session_active(p2p->cfg->cb_ctx))
		p2p_set_timeout(p2p, 0, 500000);
	else
		p2p_set_timeout(p2p, 0, 200000);
}