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
struct tcp_sock {int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  snd_nxt; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct chtls_sock {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  CSK_ABORT_SHUTDOWN ; 
 int /*<<< orphan*/  CSK_RST_ABORTED ; 
 int /*<<< orphan*/  CSK_TX_DATA_SENT ; 
 scalar_t__ TCP_SYN_RECV ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  chtls_purge_write_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_send_abort (struct sock*,int,struct sk_buff*) ; 
 scalar_t__ csk_flag_nochk (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csk_set_flag (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 scalar_t__ send_tx_flowc_wr (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void chtls_send_reset(struct sock *sk, int mode, struct sk_buff *skb)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	if (unlikely(csk_flag_nochk(csk, CSK_ABORT_SHUTDOWN) ||
		     !csk->cdev)) {
		if (sk->sk_state == TCP_SYN_RECV)
			csk_set_flag(csk, CSK_RST_ABORTED);
		goto out;
	}

	if (!csk_flag_nochk(csk, CSK_TX_DATA_SENT)) {
		struct tcp_sock *tp = tcp_sk(sk);

		if (send_tx_flowc_wr(sk, 0, tp->snd_nxt, tp->rcv_nxt) < 0)
			WARN_ONCE(1, "send tx flowc error");
		csk_set_flag(csk, CSK_TX_DATA_SENT);
	}

	csk_set_flag(csk, CSK_ABORT_RPL_PENDING);
	chtls_purge_write_queue(sk);

	csk_set_flag(csk, CSK_ABORT_SHUTDOWN);
	if (sk->sk_state != TCP_SYN_RECV)
		chtls_send_abort(sk, mode, skb);
	else
		goto out;

	return;
out:
	kfree_skb(skb);
}