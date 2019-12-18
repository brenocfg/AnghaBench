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

/* Variables and functions */
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SHUTDOWN_ELIGIBLE_STATE ; 
 int /*<<< orphan*/  chtls_close_conn (struct sock*) ; 
 scalar_t__ make_close_transition (struct sock*) ; 
 scalar_t__ sk_in_state (struct sock*,int /*<<< orphan*/ ) ; 

void chtls_shutdown(struct sock *sk, int how)
{
	if ((how & SEND_SHUTDOWN) &&
	    sk_in_state(sk, SHUTDOWN_ELIGIBLE_STATE) &&
	    make_close_transition(sk))
		chtls_close_conn(sk);
}