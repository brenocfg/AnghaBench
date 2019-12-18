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
struct sock {struct chtls_sock* sk_user_data; } ;
struct sk_buff {struct sock* sk; } ;
struct request_sock {int /*<<< orphan*/  ts_recent; } ;
struct listen_ctx {struct sock* lsk; } ;
struct chtls_sock {int txq_idx; struct chtls_dev* cdev; struct request_sock* passive_reap_next; } ;
struct chtls_dev {int /*<<< orphan*/  tids; } ;
struct TYPE_2__ {int /*<<< orphan*/  backlog_rcv; } ;

/* Variables and functions */
 TYPE_1__* BLOG_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  CPL_ABORT_NO_RST ; 
 int /*<<< orphan*/  __sk_add_backlog (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  bl_abort_syn_rcv ; 
 int /*<<< orphan*/  do_abort_syn_rcv (struct sock*,struct sock*) ; 
 void* lookup_stid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_abort_rpl (struct sock*,struct sk_buff*,struct chtls_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 

__attribute__((used)) static int abort_syn_rcv(struct sock *sk, struct sk_buff *skb)
{
	const struct request_sock *oreq;
	struct listen_ctx *listen_ctx;
	struct chtls_sock *csk;
	struct chtls_dev *cdev;
	struct sock *psk;
	void *ctx;

	csk = sk->sk_user_data;
	oreq = csk->passive_reap_next;
	cdev = csk->cdev;

	if (!oreq)
		return -1;

	ctx = lookup_stid(cdev->tids, oreq->ts_recent);
	if (!ctx)
		return -1;

	listen_ctx = (struct listen_ctx *)ctx;
	psk = listen_ctx->lsk;

	bh_lock_sock(psk);
	if (!sock_owned_by_user(psk)) {
		int queue = csk->txq_idx;

		do_abort_syn_rcv(sk, psk);
		send_abort_rpl(sk, skb, cdev, CPL_ABORT_NO_RST, queue);
	} else {
		skb->sk = sk;
		BLOG_SKB_CB(skb)->backlog_rcv = bl_abort_syn_rcv;
		__sk_add_backlog(psk, skb);
	}
	bh_unlock_sock(psk);
	return 0;
}