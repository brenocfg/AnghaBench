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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_err; struct chtls_sock* sk_user_data; } ;
struct sk_buff {int dummy; } ;
struct cpl_abort_req_rss {int /*<<< orphan*/  status; } ;
struct chtls_sock {int txq_idx; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int CPL_ABORT_NO_RST ; 
 int /*<<< orphan*/  CSK_ABORT_REQ_RCVD ; 
 int /*<<< orphan*/  CSK_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  CSK_ABORT_SHUTDOWN ; 
 int /*<<< orphan*/  CSK_TX_DATA_SENT ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int RSS_HDR ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ TCP_SYN_RECV ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  abort_syn_rcv (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  chtls_conn_done (struct sock*) ; 
 int /*<<< orphan*/  chtls_release_resources (struct sock*) ; 
 int /*<<< orphan*/  chtls_send_abort_rpl (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  chtls_set_tcb_tflag (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpl_abort_req_rss* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  csk_flag_nochk (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csk_reset_flag (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csk_set_flag (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_neg_adv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ send_tx_flowc_wr (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void chtls_abort_req_rss(struct sock *sk, struct sk_buff *skb)
{
	const struct cpl_abort_req_rss *req = cplhdr(skb) + RSS_HDR;
	struct chtls_sock *csk = sk->sk_user_data;
	int rst_status = CPL_ABORT_NO_RST;
	int queue = csk->txq_idx;

	if (is_neg_adv(req->status)) {
		if (sk->sk_state == TCP_SYN_RECV)
			chtls_set_tcb_tflag(sk, 0, 0);

		kfree_skb(skb);
		return;
	}

	csk_reset_flag(csk, CSK_ABORT_REQ_RCVD);

	if (!csk_flag_nochk(csk, CSK_ABORT_SHUTDOWN) &&
	    !csk_flag_nochk(csk, CSK_TX_DATA_SENT)) {
		struct tcp_sock *tp = tcp_sk(sk);

		if (send_tx_flowc_wr(sk, 0, tp->snd_nxt, tp->rcv_nxt) < 0)
			WARN_ONCE(1, "send_tx_flowc error");
		csk_set_flag(csk, CSK_TX_DATA_SENT);
	}

	csk_set_flag(csk, CSK_ABORT_SHUTDOWN);

	if (!csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING)) {
		sk->sk_err = ETIMEDOUT;

		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);

		if (sk->sk_state == TCP_SYN_RECV && !abort_syn_rcv(sk, skb))
			return;

		chtls_release_resources(sk);
		chtls_conn_done(sk);
	}

	chtls_send_abort_rpl(sk, skb, csk->cdev, rst_status, queue);
}