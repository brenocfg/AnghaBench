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
typedef  int u32 ;
struct tcp_sock {int copied_seq; int rcv_wup; int rcv_wnd; } ;
struct sock {int dummy; } ;
struct chtls_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREDIT_RETURN_STATE ; 
 int /*<<< orphan*/  chtls_select_window (struct sock*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int send_rx_credits (struct chtls_sock*,int) ; 
 int /*<<< orphan*/  sk_in_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void chtls_cleanup_rbuf(struct sock *sk, int copied)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct tcp_sock *tp;
	int must_send;
	u32 credits;
	u32 thres;

	thres = 15 * 1024;

	if (!sk_in_state(sk, CREDIT_RETURN_STATE))
		return;

	chtls_select_window(sk);
	tp = tcp_sk(sk);
	credits = tp->copied_seq - tp->rcv_wup;
	if (unlikely(!credits))
		return;

/*
 * For coalescing to work effectively ensure the receive window has
 * at least 16KB left.
 */
	must_send = credits + 16384 >= tp->rcv_wnd;

	if (must_send || credits >= thres)
		tp->rcv_wup += send_rx_credits(csk, credits);
}