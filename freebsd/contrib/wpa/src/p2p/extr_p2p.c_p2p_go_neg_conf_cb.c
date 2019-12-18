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
struct TYPE_3__ {int /*<<< orphan*/  p2p_device_addr; } ;
struct p2p_device {scalar_t__ go_neg_conf_sent; scalar_t__ go_neg_conf; TYPE_1__ info; int /*<<< orphan*/  go_neg_conf_freq; } ;
struct p2p_data {TYPE_2__* cfg; int /*<<< orphan*/  pending_action_state; struct p2p_device* go_neg_peer; } ;
typedef  enum p2p_send_action_result { ____Placeholder_p2p_send_action_result } p2p_send_action_result ;
struct TYPE_4__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* send_action_done ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ P2P_GO_NEG_CNF_MAX_RETRY_COUNT ; 
 int /*<<< orphan*/  P2P_PENDING_GO_NEG_CONFIRM ; 
 int P2P_SEND_ACTION_FAILED ; 
 int P2P_SEND_ACTION_NO_ACK ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,...) ; 
 int /*<<< orphan*/  p2p_go_complete (struct p2p_data*,struct p2p_device*) ; 
 int /*<<< orphan*/  p2p_go_neg_failed (struct p2p_data*,int) ; 
 scalar_t__ p2p_send_action (struct p2p_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_len (scalar_t__) ; 

__attribute__((used)) static void p2p_go_neg_conf_cb(struct p2p_data *p2p,
			       enum p2p_send_action_result result)
{
	struct p2p_device *dev;

	p2p_dbg(p2p, "GO Negotiation Confirm TX callback: result=%d", result);
	if (result == P2P_SEND_ACTION_FAILED) {
		p2p->cfg->send_action_done(p2p->cfg->cb_ctx);
		p2p_go_neg_failed(p2p, -1);
		return;
	}

	dev = p2p->go_neg_peer;

	if (result == P2P_SEND_ACTION_NO_ACK) {
		/*
		 * Retry GO Negotiation Confirmation
		 * P2P_GO_NEG_CNF_MAX_RETRY_COUNT times if we did not receive
		 * ACK for confirmation.
		 */
		if (dev && dev->go_neg_conf &&
		    dev->go_neg_conf_sent <= P2P_GO_NEG_CNF_MAX_RETRY_COUNT) {
			p2p_dbg(p2p, "GO Negotiation Confirm retry %d",
				dev->go_neg_conf_sent);
			p2p->pending_action_state = P2P_PENDING_GO_NEG_CONFIRM;
			if (p2p_send_action(p2p, dev->go_neg_conf_freq,
					    dev->info.p2p_device_addr,
					    p2p->cfg->dev_addr,
					    dev->info.p2p_device_addr,
					    wpabuf_head(dev->go_neg_conf),
					    wpabuf_len(dev->go_neg_conf), 0) >=
			    0) {
				dev->go_neg_conf_sent++;
				return;
			}
			p2p_dbg(p2p, "Failed to re-send Action frame");

			/*
			 * Continue with the assumption that the first attempt
			 * went through and just the ACK frame was lost.
			 */
		}

		/*
		 * It looks like the TX status for GO Negotiation Confirm is
		 * often showing failure even when the peer has actually
		 * received the frame. Since the peer may change channels
		 * immediately after having received the frame, we may not see
		 * an Ack for retries, so just dropping a single frame may
		 * trigger this. To allow the group formation to succeed if the
		 * peer did indeed receive the frame, continue regardless of
		 * the TX status.
		 */
		p2p_dbg(p2p, "Assume GO Negotiation Confirm TX was actually received by the peer even though Ack was not reported");
	}

	p2p->cfg->send_action_done(p2p->cfg->cb_ctx);

	if (dev == NULL)
		return;

	p2p_go_complete(p2p, dev);
}