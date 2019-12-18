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
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct l2t_entry {int dummy; } ;
struct cpl_abort_rpl {int dummy; } ;
struct cpl_abort_req_rss {int status; } ;
struct chtls_sock {int /*<<< orphan*/  egress_dev; struct l2t_entry* l2t_entry; } ;
struct chtls_dev {TYPE_1__* lldi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 unsigned int GET_TID (struct cpl_abort_req_rss*) ; 
 int RSS_HDR ; 
 scalar_t__ TCP_SYN_RECV ; 
 struct cpl_abort_req_rss* cplhdr (struct sk_buff*) ; 
 scalar_t__ csk_conn_inline (struct chtls_sock*) ; 
 int /*<<< orphan*/  cxgb4_l2t_send (int /*<<< orphan*/ ,struct sk_buff*,struct l2t_entry*) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* get_cpl_skb (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  send_defer_abort_rpl ; 
 int /*<<< orphan*/  set_abort_rpl_wr (struct sk_buff*,unsigned int,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_defer_reply (struct sk_buff*,struct chtls_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chtls_send_abort_rpl(struct sock *sk, struct sk_buff *skb,
				 struct chtls_dev *cdev,
				 int status, int queue)
{
	struct cpl_abort_req_rss *req = cplhdr(skb) + RSS_HDR;
	struct sk_buff *reply_skb;
	struct chtls_sock *csk;
	unsigned int tid;

	csk = rcu_dereference_sk_user_data(sk);
	tid = GET_TID(req);

	reply_skb = get_cpl_skb(skb, sizeof(struct cpl_abort_rpl), gfp_any());
	if (!reply_skb) {
		req->status = (queue << 1) | status;
		t4_defer_reply(skb, cdev, send_defer_abort_rpl);
		return;
	}

	set_abort_rpl_wr(reply_skb, tid, status);
	set_wr_txq(reply_skb, CPL_PRIORITY_DATA, queue);
	if (csk_conn_inline(csk)) {
		struct l2t_entry *e = csk->l2t_entry;

		if (e && sk->sk_state != TCP_SYN_RECV) {
			cxgb4_l2t_send(csk->egress_dev, reply_skb, e);
			return;
		}
	}
	cxgb4_ofld_send(cdev->lldi->ports[0], reply_skb);
	kfree_skb(skb);
}