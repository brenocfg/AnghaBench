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
struct p2p_data {int /*<<< orphan*/  invite_dev_pw_id; int /*<<< orphan*/  invite_go_dev_addr; int /*<<< orphan*/ * invite_peer; TYPE_1__* cfg; scalar_t__ pending_listen_freq; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* stop_listen ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_invite_send (struct p2p_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_invite_start(void *eloop_ctx, void *timeout_ctx)
{
	struct p2p_data *p2p = eloop_ctx;
	if (p2p->invite_peer == NULL)
		return;
	if (p2p->pending_listen_freq) {
		p2p_dbg(p2p, "Clear pending_listen_freq for p2p_invite_start");
		p2p->pending_listen_freq = 0;
	}
	p2p->cfg->stop_listen(p2p->cfg->cb_ctx);
	p2p_invite_send(p2p, p2p->invite_peer, p2p->invite_go_dev_addr,
			p2p->invite_dev_pw_id);
}