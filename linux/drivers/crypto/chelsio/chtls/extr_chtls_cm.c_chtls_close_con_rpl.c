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
struct tcp_sock {int /*<<< orphan*/  linger2; scalar_t__ snd_una; } ;
struct sock {int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; } ;
struct sk_buff {int dummy; } ;
struct cpl_close_con_rpl {int /*<<< orphan*/  snd_nxt; } ;
struct chtls_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_ABORT_RPL_PENDING ; 
 int /*<<< orphan*/  CSK_ABORT_SHUTDOWN ; 
 int RSS_HDR ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
#define  TCP_CLOSING 130 
#define  TCP_FIN_WAIT1 129 
 int /*<<< orphan*/  TCP_FIN_WAIT2 ; 
#define  TCP_LAST_ACK 128 
 int /*<<< orphan*/  chtls_abort_conn (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  chtls_conn_done (struct sock*) ; 
 int /*<<< orphan*/  chtls_release_resources (struct sock*) ; 
 int /*<<< orphan*/  chtls_timewait (struct sock*) ; 
 struct cpl_close_con_rpl* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  csk_flag_nochk (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void chtls_close_con_rpl(struct sock *sk, struct sk_buff *skb)
{
	struct cpl_close_con_rpl *rpl = cplhdr(skb) + RSS_HDR;
	struct chtls_sock *csk;
	struct tcp_sock *tp;

	csk = rcu_dereference_sk_user_data(sk);
	tp = tcp_sk(sk);

	tp->snd_una = ntohl(rpl->snd_nxt) - 1;  /* exclude FIN */

	switch (sk->sk_state) {
	case TCP_CLOSING:
		chtls_release_resources(sk);
		if (csk_flag_nochk(csk, CSK_ABORT_RPL_PENDING))
			chtls_conn_done(sk);
		else
			chtls_timewait(sk);
		break;
	case TCP_LAST_ACK:
		chtls_release_resources(sk);
		chtls_conn_done(sk);
		break;
	case TCP_FIN_WAIT1:
		tcp_set_state(sk, TCP_FIN_WAIT2);
		sk->sk_shutdown |= SEND_SHUTDOWN;

		if (!sock_flag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		else if (tcp_sk(sk)->linger2 < 0 &&
			 !csk_flag_nochk(csk, CSK_ABORT_SHUTDOWN))
			chtls_abort_conn(sk, skb);
		break;
	default:
		pr_info("close_con_rpl in bad state %d\n", sk->sk_state);
	}
	kfree_skb(skb);
}