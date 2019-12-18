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
struct chtls_sock {struct sk_buff* wr_skb_head; } ;
struct TYPE_2__ {struct sk_buff* next_wr; } ;

/* Variables and functions */
 TYPE_1__* WR_SKB_CB (struct sk_buff*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 

__attribute__((used)) static struct sk_buff *dequeue_wr(struct sock *sk)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct sk_buff *skb = csk->wr_skb_head;

	if (likely(skb)) {
	/* Don't bother clearing the tail */
		csk->wr_skb_head = WR_SKB_CB(skb)->next_wr;
		WR_SKB_CB(skb)->next_wr = NULL;
	}
	return skb;
}