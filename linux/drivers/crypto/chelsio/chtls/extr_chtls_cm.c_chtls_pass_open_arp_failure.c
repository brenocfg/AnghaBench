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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int /*<<< orphan*/  ts_recent; } ;
struct listen_ctx {struct sock* lsk; } ;
struct chtls_sock {struct request_sock* passive_reap_next; struct chtls_dev* cdev; } ;
struct chtls_dev {int /*<<< orphan*/  tids; } ;
struct TYPE_2__ {int /*<<< orphan*/  backlog_rcv; } ;

/* Variables and functions */
 TYPE_1__* BLOG_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  CSK_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  __sk_add_backlog (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  bl_pass_open_abort ; 
 scalar_t__ csk_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* lookup_stid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass_open_abort (struct sock*,struct sock*,struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 

__attribute__((used)) static void chtls_pass_open_arp_failure(struct sock *sk,
					struct sk_buff *skb)
{
	const struct request_sock *oreq;
	struct chtls_sock *csk;
	struct chtls_dev *cdev;
	struct sock *parent;
	void *data;

	csk = rcu_dereference_sk_user_data(sk);
	cdev = csk->cdev;

	/*
	 * If the connection is being aborted due to the parent listening
	 * socket going away there's nothing to do, the ABORT_REQ will close
	 * the connection.
	 */
	if (csk_flag(sk, CSK_ABORT_RPL_PENDING)) {
		kfree_skb(skb);
		return;
	}

	oreq = csk->passive_reap_next;
	data = lookup_stid(cdev->tids, oreq->ts_recent);
	parent = ((struct listen_ctx *)data)->lsk;

	bh_lock_sock(parent);
	if (!sock_owned_by_user(parent)) {
		pass_open_abort(sk, parent, skb);
	} else {
		BLOG_SKB_CB(skb)->backlog_rcv = bl_pass_open_abort;
		__sk_add_backlog(parent, skb);
	}
	bh_unlock_sock(parent);
}