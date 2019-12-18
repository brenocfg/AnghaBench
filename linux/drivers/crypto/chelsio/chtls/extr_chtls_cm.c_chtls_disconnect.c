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
struct TYPE_2__ {int snd_wscale; } ;
struct tcp_sock {int max_window; TYPE_1__ rx_opt; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPL_ABORT_SEND_RST ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  TCPF_CLOSE ; 
 scalar_t__ TCP_CLOSE ; 
 int /*<<< orphan*/  chtls_purge_receive_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_purge_recv_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_purge_write_queue (struct sock*) ; 
 int /*<<< orphan*/  chtls_send_reset (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tcp_disconnect (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int wait_for_states (struct sock*,int /*<<< orphan*/ ) ; 

int chtls_disconnect(struct sock *sk, int flags)
{
	struct tcp_sock *tp;
	int err;

	tp = tcp_sk(sk);
	chtls_purge_recv_queue(sk);
	chtls_purge_receive_queue(sk);
	chtls_purge_write_queue(sk);

	if (sk->sk_state != TCP_CLOSE) {
		sk->sk_err = ECONNRESET;
		chtls_send_reset(sk, CPL_ABORT_SEND_RST, NULL);
		err = wait_for_states(sk, TCPF_CLOSE);
		if (err)
			return err;
	}
	chtls_purge_recv_queue(sk);
	chtls_purge_receive_queue(sk);
	tp->max_window = 0xFFFF << (tp->rx_opt.snd_wscale);
	return tcp_disconnect(sk, flags);
}