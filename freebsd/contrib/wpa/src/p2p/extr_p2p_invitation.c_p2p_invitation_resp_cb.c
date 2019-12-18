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
struct p2p_data {int /*<<< orphan*/  inv_op_freq; int /*<<< orphan*/  inv_status; int /*<<< orphan*/  inv_go_dev_addr; int /*<<< orphan*/  inv_ssid_len; int /*<<< orphan*/  inv_ssid; int /*<<< orphan*/  inv_group_bssid_ptr; int /*<<< orphan*/  inv_sa; TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* invitation_received ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_action_done ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void p2p_invitation_resp_cb(struct p2p_data *p2p, int success)
{
	p2p_dbg(p2p, "Invitation Response TX callback: success=%d", success);
	p2p->cfg->send_action_done(p2p->cfg->cb_ctx);

	if (!success)
		p2p_dbg(p2p, "Assume Invitation Response was actually received by the peer even though Ack was not reported");

	if (p2p->cfg->invitation_received) {
		p2p->cfg->invitation_received(p2p->cfg->cb_ctx,
					      p2p->inv_sa,
					      p2p->inv_group_bssid_ptr,
					      p2p->inv_ssid, p2p->inv_ssid_len,
					      p2p->inv_go_dev_addr,
					      p2p->inv_status,
					      p2p->inv_op_freq);
	}
}