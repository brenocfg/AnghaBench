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
typedef  struct wpabuf const wpabuf ;
struct p2p_data {TYPE_1__* cfg; int /*<<< orphan*/  pending_action_state; int /*<<< orphan*/  srv_update_indic; scalar_t__ sd_frag_id; scalar_t__ sd_resp_pos; int /*<<< orphan*/  sd_resp_dialog_token; int /*<<< orphan*/  sd_resp_addr; struct wpabuf const* sd_resp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  P2P_NO_PENDING_ACTION ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct wpabuf const* p2p_build_sd_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wpabuf const*) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_err (struct p2p_data*,char*) ; 
 scalar_t__ p2p_send_action (struct p2p_data*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,unsigned int) ; 
 struct wpabuf const* wpabuf_dup (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 

void p2p_sd_response(struct p2p_data *p2p, int freq, const u8 *dst,
		     u8 dialog_token, const struct wpabuf *resp_tlvs)
{
	struct wpabuf *resp;
	size_t max_len;
	unsigned int wait_time = 200;

	/*
	 * In the 60 GHz, we have a smaller maximum frame length for management
	 * frames.
	 */
	max_len = (freq > 56160) ? 928 : 1400;

	/* TODO: fix the length limit to match with the maximum frame length */
	if (wpabuf_len(resp_tlvs) > max_len) {
		p2p_dbg(p2p, "SD response long enough to require fragmentation");
		if (p2p->sd_resp) {
			/*
			 * TODO: Could consider storing the fragmented response
			 * separately for each peer to avoid having to drop old
			 * one if there is more than one pending SD query.
			 * Though, that would eat more memory, so there are
			 * also benefits to just using a single buffer.
			 */
			p2p_dbg(p2p, "Drop previous SD response");
			wpabuf_free(p2p->sd_resp);
		}
		p2p->sd_resp = wpabuf_dup(resp_tlvs);
		if (p2p->sd_resp == NULL) {
			p2p_err(p2p, "Failed to allocate SD response fragmentation area");
			return;
		}
		os_memcpy(p2p->sd_resp_addr, dst, ETH_ALEN);
		p2p->sd_resp_dialog_token = dialog_token;
		p2p->sd_resp_pos = 0;
		p2p->sd_frag_id = 0;
		resp = p2p_build_sd_response(dialog_token, WLAN_STATUS_SUCCESS,
					     1, p2p->srv_update_indic, NULL);
	} else {
		p2p_dbg(p2p, "SD response fits in initial response");
		wait_time = 0; /* no more SD frames in the sequence */
		resp = p2p_build_sd_response(dialog_token,
					     WLAN_STATUS_SUCCESS, 0,
					     p2p->srv_update_indic, resp_tlvs);
	}
	if (resp == NULL)
		return;

	p2p->pending_action_state = P2P_NO_PENDING_ACTION;
	if (p2p_send_action(p2p, freq, dst, p2p->cfg->dev_addr,
			    p2p->cfg->dev_addr,
			    wpabuf_head(resp), wpabuf_len(resp), wait_time) < 0)
		p2p_dbg(p2p, "Failed to send Action frame");

	wpabuf_free(resp);
}