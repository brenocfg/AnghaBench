#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct p2p_data {scalar_t__ state; TYPE_4__* invite_peer; TYPE_2__* go_neg_peer; } ;
typedef  enum p2p_probe_req_status { ____Placeholder_p2p_probe_req_status } p2p_probe_req_status ;
struct TYPE_7__ {int /*<<< orphan*/  p2p_device_addr; } ;
struct TYPE_8__ {int flags; TYPE_3__ info; } ;
struct TYPE_5__ {int /*<<< orphan*/  p2p_device_addr; } ;
struct TYPE_6__ {int flags; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ P2P_CONNECT ; 
 scalar_t__ P2P_CONNECT_LISTEN ; 
 int P2P_DEV_WAIT_GO_NEG_CONFIRM ; 
 int P2P_DEV_WAIT_INV_REQ_ACK ; 
 scalar_t__ P2P_INVITE ; 
 scalar_t__ P2P_INVITE_LISTEN ; 
 int P2P_PREQ_NOT_PROCESSED ; 
 int P2P_PREQ_PROCESSED ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct p2p_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_add_dev_from_probe_req (struct p2p_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_go_neg_start ; 
 int /*<<< orphan*/  p2p_invite_start ; 
 int p2p_reply_probe (struct p2p_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,unsigned int) ; 

enum p2p_probe_req_status
p2p_probe_req_rx(struct p2p_data *p2p, const u8 *addr, const u8 *dst,
		 const u8 *bssid, const u8 *ie, size_t ie_len,
		 unsigned int rx_freq, int p2p_lo_started)
{
	enum p2p_probe_req_status res;

	p2p_add_dev_from_probe_req(p2p, addr, ie, ie_len);

	if (p2p_lo_started) {
		p2p_dbg(p2p,
			"Probe Response is offloaded, do not reply Probe Request");
		return P2P_PREQ_PROCESSED;
	}

	res = p2p_reply_probe(p2p, addr, dst, bssid, ie, ie_len, rx_freq);
	if (res != P2P_PREQ_PROCESSED && res != P2P_PREQ_NOT_PROCESSED)
		return res;

	/*
	 * Activate a pending GO Negotiation/Invite flow if a received Probe
	 * Request frame is from an expected peer. Some devices may share the
	 * same address for P2P and non-P2P STA running simultaneously. The
	 * P2P_PREQ_PROCESSED and P2P_PREQ_NOT_PROCESSED p2p_reply_probe()
	 * return values verified above ensure we are handling a Probe Request
	 * frame from a P2P peer.
	 */
	if ((p2p->state == P2P_CONNECT || p2p->state == P2P_CONNECT_LISTEN) &&
	    p2p->go_neg_peer &&
	    os_memcmp(addr, p2p->go_neg_peer->info.p2p_device_addr, ETH_ALEN)
	    == 0 &&
	    !(p2p->go_neg_peer->flags & P2P_DEV_WAIT_GO_NEG_CONFIRM)) {
		/* Received a Probe Request from GO Negotiation peer */
		p2p_dbg(p2p, "Found GO Negotiation peer - try to start GO negotiation from timeout");
		eloop_cancel_timeout(p2p_go_neg_start, p2p, NULL);
		eloop_register_timeout(0, 0, p2p_go_neg_start, p2p, NULL);
		return res;
	}

	if ((p2p->state == P2P_INVITE || p2p->state == P2P_INVITE_LISTEN) &&
	    p2p->invite_peer &&
	    (p2p->invite_peer->flags & P2P_DEV_WAIT_INV_REQ_ACK) &&
	    os_memcmp(addr, p2p->invite_peer->info.p2p_device_addr, ETH_ALEN)
	    == 0) {
		/* Received a Probe Request from Invite peer */
		p2p_dbg(p2p, "Found Invite peer - try to start Invite from timeout");
		eloop_cancel_timeout(p2p_invite_start, p2p, NULL);
		eloop_register_timeout(0, 0, p2p_invite_start, p2p, NULL);
		return res;
	}

	return res;
}