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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;struct chtls_sock* sk_user_data; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int /*<<< orphan*/  rsk_refcnt; } ;
struct chtls_sock {TYPE_1__* listen_ctx; int /*<<< orphan*/  synq; struct request_sock* passive_reap_next; } ;
struct chtls_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  icsk_accept_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  synq; } ;

/* Variables and functions */
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_to_reap_list (struct sock*) ; 
 int /*<<< orphan*/  chtls_reqsk_free (struct request_sock*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_add (struct sock*,struct request_sock*,struct sock*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reqsk_queue_removed (int /*<<< orphan*/ *,struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void add_pass_open_to_parent(struct sock *child, struct sock *lsk,
				    struct chtls_dev *cdev)
{
	struct request_sock *oreq;
	struct chtls_sock *csk;

	if (lsk->sk_state != TCP_LISTEN)
		return;

	csk = child->sk_user_data;
	oreq = csk->passive_reap_next;
	csk->passive_reap_next = NULL;

	reqsk_queue_removed(&inet_csk(lsk)->icsk_accept_queue, oreq);
	__skb_unlink((struct sk_buff *)&csk->synq, &csk->listen_ctx->synq);

	if (sk_acceptq_is_full(lsk)) {
		chtls_reqsk_free(oreq);
		add_to_reap_list(child);
	} else {
		refcount_set(&oreq->rsk_refcnt, 1);
		inet_csk_reqsk_queue_add(lsk, oreq, child);
		lsk->sk_data_ready(lsk);
	}
}