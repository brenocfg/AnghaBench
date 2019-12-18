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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct chtls_sock {struct request_sock* passive_reap_next; TYPE_1__* listen_ctx; int /*<<< orphan*/  synq; } ;
struct TYPE_4__ {int /*<<< orphan*/  icsk_accept_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  synq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chtls_reqsk_free (struct request_sock*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  reqsk_queue_removed (int /*<<< orphan*/ *,struct request_sock*) ; 

__attribute__((used)) static void cleanup_syn_rcv_conn(struct sock *child, struct sock *parent)
{
	struct request_sock *req;
	struct chtls_sock *csk;

	csk = rcu_dereference_sk_user_data(child);
	req = csk->passive_reap_next;

	reqsk_queue_removed(&inet_csk(parent)->icsk_accept_queue, req);
	__skb_unlink((struct sk_buff *)&csk->synq, &csk->listen_ctx->synq);
	chtls_reqsk_free(req);
	csk->passive_reap_next = NULL;
}