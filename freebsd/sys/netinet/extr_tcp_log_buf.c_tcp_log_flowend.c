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
struct tcpcb {scalar_t__ t_logstate; TYPE_1__* t_inpcb; } ;
struct socket {int /*<<< orphan*/  so_snd; int /*<<< orphan*/  so_rcv; } ;
struct TYPE_2__ {struct socket* inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_LOG_EVENT (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TCP_LOG_FLOWEND ; 
 scalar_t__ TCP_LOG_STATE_OFF ; 

void
tcp_log_flowend(struct tcpcb *tp)
{
	if (tp->t_logstate != TCP_LOG_STATE_OFF) {
		struct socket *so = tp->t_inpcb->inp_socket;
		TCP_LOG_EVENT(tp, NULL, &so->so_rcv, &so->so_snd,
				TCP_LOG_FLOWEND, 0, 0, NULL, false);
	}
}