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
struct tcp_sock {int nonagle; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int TCP_NAGLE_CORK ; 
 int /*<<< orphan*/  chtls_tcp_push (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_uncork(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tp->nonagle & TCP_NAGLE_CORK) {
		tp->nonagle &= ~TCP_NAGLE_CORK;
		chtls_tcp_push(sk, 0);
	}
}