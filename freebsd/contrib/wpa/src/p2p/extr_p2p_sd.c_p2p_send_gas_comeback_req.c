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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct p2p_data {TYPE_1__* cfg; int /*<<< orphan*/  pending_action_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_NO_PENDING_ACTION ; 
 struct wpabuf* gas_build_comeback_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 scalar_t__ p2p_send_action (struct p2p_data*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void p2p_send_gas_comeback_req(struct p2p_data *p2p, const u8 *dst,
				      u8 dialog_token, int freq)
{
	struct wpabuf *req;

	req = gas_build_comeback_req(dialog_token);
	if (req == NULL)
		return;

	p2p->pending_action_state = P2P_NO_PENDING_ACTION;
	if (p2p_send_action(p2p, freq, dst, p2p->cfg->dev_addr, dst,
			    wpabuf_head(req), wpabuf_len(req), 200) < 0)
		p2p_dbg(p2p, "Failed to send Action frame");

	wpabuf_free(req);
}