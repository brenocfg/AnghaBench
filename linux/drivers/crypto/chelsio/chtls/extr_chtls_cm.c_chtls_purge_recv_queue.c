#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct chtls_hws {int /*<<< orphan*/  sk_recv_queue; } ;
struct chtls_sock {struct chtls_hws tlshws; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chtls_purge_recv_queue(struct sock *sk)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct chtls_hws *tlsk = &csk->tlshws;
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(&tlsk->sk_recv_queue)) != NULL) {
		skb_dst_set(skb, NULL);
		kfree_skb(skb);
	}
}