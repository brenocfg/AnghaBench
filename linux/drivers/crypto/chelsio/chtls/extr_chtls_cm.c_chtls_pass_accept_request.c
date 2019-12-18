#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct vlan_ethhdr {int dummy; } ;
struct tcphdr {scalar_t__ cwr; scalar_t__ ece; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; int /*<<< orphan*/  seq; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {struct sock* sk; } ;
struct request_sock {scalar_t__ ts_recent; scalar_t__ mss; scalar_t__ cookie_ts; scalar_t__ rsk_window_clamp; scalar_t__ rsk_rcv_wnd; } ;
struct listen_ctx {int /*<<< orphan*/  synq; } ;
struct iphdr {int version; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ethhdr {int dummy; } ;
struct cpl_t5_pass_accept_rpl {int dummy; } ;
struct TYPE_8__ {int wsf; } ;
struct cpl_pass_accept_req {TYPE_1__ tcpopt; int /*<<< orphan*/  hdr_len; int /*<<< orphan*/  tos_stid; } ;
struct chtls_sock {int /*<<< orphan*/  synq; struct listen_ctx* listen_ctx; } ;
struct chtls_dev {TYPE_3__* lldi; int /*<<< orphan*/  tids; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_14__ {struct chtls_dev* cdev; } ;
struct TYPE_13__ {int wscale_ok; int snd_wscale; int ecn_ok; int /*<<< orphan*/  ir_iif; } ;
struct TYPE_9__ {int sysctl_tcp_ecn; scalar_t__ sysctl_tcp_window_scaling; } ;
struct TYPE_12__ {TYPE_2__ ipv4; } ;
struct TYPE_11__ {int tfo_listener; int /*<<< orphan*/  rcv_isn; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 TYPE_7__* BLOG_SKB_CB (struct sk_buff*) ; 
 scalar_t__ ETH_HLEN ; 
 unsigned int GET_TID (struct cpl_pass_accept_req*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INET_ECN_is_not_ect (int /*<<< orphan*/ ) ; 
 unsigned int PASS_OPEN_TID_G (int /*<<< orphan*/ ) ; 
 int RSS_HDR ; 
 scalar_t__ T6_ETH_HDR_LEN_G (int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ chtls_get_module (struct sock*) ; 
 int /*<<< orphan*/  chtls_install_cpl_ops (struct sock*) ; 
 int /*<<< orphan*/  chtls_pass_accept_rpl (struct sk_buff*,struct cpl_pass_accept_req*,unsigned int) ; 
 struct sock* chtls_recv_sock (struct sock*,struct request_sock*,void*,struct cpl_pass_accept_req*,struct chtls_dev*) ; 
 int /*<<< orphan*/  chtls_reqsk_free (struct request_sock*) ; 
 int /*<<< orphan*/  chtls_rsk_ops ; 
 int /*<<< orphan*/  chtls_set_req_addr (struct request_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chtls_set_req_port (struct request_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpl_pass_accept_req* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb4_insert_tid (int /*<<< orphan*/ ,struct sock*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb4_remove_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_added (struct sock*) ; 
 scalar_t__ inet_csk_reqsk_queue_is_full (struct sock*) ; 
 struct request_sock* inet_reqsk_alloc (int /*<<< orphan*/ *,struct sock*,int) ; 
 TYPE_6__* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  ipv4_get_dsfield (struct iphdr*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ lookup_stid (int /*<<< orphan*/ ,unsigned int) ; 
 struct sock* lookup_tid (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mk_tid_release (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 unsigned int roundup (int,int) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 TYPE_5__* sock_net (struct sock*) ; 
 scalar_t__ tcp_ca_needs_ecn (struct sock*) ; 
 TYPE_4__* tcp_rsk (struct request_sock*) ; 

__attribute__((used)) static void chtls_pass_accept_request(struct sock *sk,
				      struct sk_buff *skb)
{
	struct cpl_t5_pass_accept_rpl *rpl;
	struct cpl_pass_accept_req *req;
	struct listen_ctx *listen_ctx;
	struct vlan_ethhdr *vlan_eh;
	struct request_sock *oreq;
	struct sk_buff *reply_skb;
	struct chtls_sock *csk;
	struct chtls_dev *cdev;
	struct tcphdr *tcph;
	struct sock *newsk;
	struct ethhdr *eh;
	struct iphdr *iph;
	void *network_hdr;
	unsigned int stid;
	unsigned int len;
	unsigned int tid;
	bool th_ecn, ect;
	__u8 ip_dsfield; /* IPv4 tos or IPv6 dsfield */
	u16 eth_hdr_len;
	bool ecn_ok;

	req = cplhdr(skb) + RSS_HDR;
	tid = GET_TID(req);
	cdev = BLOG_SKB_CB(skb)->cdev;
	newsk = lookup_tid(cdev->tids, tid);
	stid = PASS_OPEN_TID_G(ntohl(req->tos_stid));
	if (newsk) {
		pr_info("tid (%d) already in use\n", tid);
		return;
	}

	len = roundup(sizeof(*rpl), 16);
	reply_skb = alloc_skb(len, GFP_ATOMIC);
	if (!reply_skb) {
		cxgb4_remove_tid(cdev->tids, 0, tid, sk->sk_family);
		kfree_skb(skb);
		return;
	}

	if (sk->sk_state != TCP_LISTEN)
		goto reject;

	if (inet_csk_reqsk_queue_is_full(sk))
		goto reject;

	if (sk_acceptq_is_full(sk))
		goto reject;

	oreq = inet_reqsk_alloc(&chtls_rsk_ops, sk, true);
	if (!oreq)
		goto reject;

	oreq->rsk_rcv_wnd = 0;
	oreq->rsk_window_clamp = 0;
	oreq->cookie_ts = 0;
	oreq->mss = 0;
	oreq->ts_recent = 0;

	eth_hdr_len = T6_ETH_HDR_LEN_G(ntohl(req->hdr_len));
	if (eth_hdr_len == ETH_HLEN) {
		eh = (struct ethhdr *)(req + 1);
		iph = (struct iphdr *)(eh + 1);
		network_hdr = (void *)(eh + 1);
	} else {
		vlan_eh = (struct vlan_ethhdr *)(req + 1);
		iph = (struct iphdr *)(vlan_eh + 1);
		network_hdr = (void *)(vlan_eh + 1);
	}
	if (iph->version != 0x4)
		goto free_oreq;

	tcph = (struct tcphdr *)(iph + 1);
	skb_set_network_header(skb, (void *)iph - (void *)req);

	tcp_rsk(oreq)->tfo_listener = false;
	tcp_rsk(oreq)->rcv_isn = ntohl(tcph->seq);
	chtls_set_req_port(oreq, tcph->source, tcph->dest);
	chtls_set_req_addr(oreq, iph->daddr, iph->saddr);
	ip_dsfield = ipv4_get_dsfield(iph);
	if (req->tcpopt.wsf <= 14 &&
	    sock_net(sk)->ipv4.sysctl_tcp_window_scaling) {
		inet_rsk(oreq)->wscale_ok = 1;
		inet_rsk(oreq)->snd_wscale = req->tcpopt.wsf;
	}
	inet_rsk(oreq)->ir_iif = sk->sk_bound_dev_if;
	th_ecn = tcph->ece && tcph->cwr;
	if (th_ecn) {
		ect = !INET_ECN_is_not_ect(ip_dsfield);
		ecn_ok = sock_net(sk)->ipv4.sysctl_tcp_ecn;
		if ((!ect && ecn_ok) || tcp_ca_needs_ecn(sk))
			inet_rsk(oreq)->ecn_ok = 1;
	}

	newsk = chtls_recv_sock(sk, oreq, network_hdr, req, cdev);
	if (!newsk)
		goto reject;

	if (chtls_get_module(newsk))
		goto reject;
	inet_csk_reqsk_queue_added(sk);
	reply_skb->sk = newsk;
	chtls_install_cpl_ops(newsk);
	cxgb4_insert_tid(cdev->tids, newsk, tid, newsk->sk_family);
	csk = rcu_dereference_sk_user_data(newsk);
	listen_ctx = (struct listen_ctx *)lookup_stid(cdev->tids, stid);
	csk->listen_ctx = listen_ctx;
	__skb_queue_tail(&listen_ctx->synq, (struct sk_buff *)&csk->synq);
	chtls_pass_accept_rpl(reply_skb, req, tid);
	kfree_skb(skb);
	return;

free_oreq:
	chtls_reqsk_free(oreq);
reject:
	mk_tid_release(reply_skb, 0, tid);
	cxgb4_ofld_send(cdev->lldi->ports[0], reply_skb);
	kfree_skb(skb);
}