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
struct tcp_sock {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct chtls_sock {int /*<<< orphan*/  txq; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ULPCB_FLAG_HOLD ; 
 int ULPCB_FLAG_NO_APPEND ; 
 TYPE_1__* ULP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  chtls_push_frames (struct chtls_sock*,int) ; 
 scalar_t__ corked (struct tcp_sock*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mark_urg (struct tcp_sock*,int,struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 scalar_t__ should_push (struct sock*) ; 
 struct sk_buff* skb_peek_tail (int /*<<< orphan*/ *) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void chtls_tcp_push(struct sock *sk, int flags)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	int qlen = skb_queue_len(&csk->txq);

	if (likely(qlen)) {
		struct sk_buff *skb = skb_peek_tail(&csk->txq);
		struct tcp_sock *tp = tcp_sk(sk);

		mark_urg(tp, flags, skb);

		if (!(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND) &&
		    corked(tp, flags)) {
			ULP_SKB_CB(skb)->flags |= ULPCB_FLAG_HOLD;
			return;
		}

		ULP_SKB_CB(skb)->flags &= ~ULPCB_FLAG_HOLD;
		if (qlen == 1 &&
		    ((ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND) ||
		     should_push(sk)))
			chtls_push_frames(csk, 1);
	}
}