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
struct p2p_data {scalar_t__ pending_action_state; scalar_t__ pd_retries; scalar_t__ state; int ext_listen_only; int /*<<< orphan*/  ext_listen_period; TYPE_1__* cfg; int /*<<< orphan*/  ext_listen_interval_usec; int /*<<< orphan*/  ext_listen_interval_sec; scalar_t__ ext_listen_interval; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_ctx; scalar_t__ (* is_p2p_in_progress ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ P2P_IDLE ; 
 scalar_t__ P2P_LISTEN_ONLY ; 
 scalar_t__ P2P_PENDING_PD ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,void*),struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 scalar_t__ p2p_listen (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_state (struct p2p_data*,scalar_t__) ; 
 int /*<<< orphan*/  p2p_state_txt (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_ext_listen_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct p2p_data *p2p = eloop_ctx;

	if (p2p->ext_listen_interval) {
		/* Schedule next extended listen timeout */
		eloop_register_timeout(p2p->ext_listen_interval_sec,
				       p2p->ext_listen_interval_usec,
				       p2p_ext_listen_timeout, p2p, NULL);
	}

	if ((p2p->cfg->is_p2p_in_progress &&
	     p2p->cfg->is_p2p_in_progress(p2p->cfg->cb_ctx)) ||
	    (p2p->pending_action_state == P2P_PENDING_PD &&
	     p2p->pd_retries > 0)) {
		p2p_dbg(p2p, "Operation in progress - skip Extended Listen timeout (%s)",
			p2p_state_txt(p2p->state));
		return;
	}

	if (p2p->state == P2P_LISTEN_ONLY && p2p->ext_listen_only) {
		/*
		 * This should not really happen, but it looks like the Listen
		 * command may fail is something else (e.g., a scan) was
		 * running at an inconvenient time. As a workaround, allow new
		 * Extended Listen operation to be started.
		 */
		p2p_dbg(p2p, "Previous Extended Listen operation had not been completed - try again");
		p2p->ext_listen_only = 0;
		p2p_set_state(p2p, P2P_IDLE);
	}

	if (p2p->state != P2P_IDLE) {
		p2p_dbg(p2p, "Skip Extended Listen timeout in active state (%s)", p2p_state_txt(p2p->state));
		return;
	}

	p2p_dbg(p2p, "Extended Listen timeout");
	p2p->ext_listen_only = 1;
	if (p2p_listen(p2p, p2p->ext_listen_period) < 0) {
		p2p_dbg(p2p, "Failed to start Listen state for Extended Listen Timing");
		p2p->ext_listen_only = 0;
	}
}