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
struct tcpcb {int /*<<< orphan*/  t_inpcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (void (*) (struct tcpcb*),struct tcpcb*) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 

void
tcp_offload_listen_stop(struct tcpcb *tp)
{

	INP_WLOCK_ASSERT(tp->t_inpcb);

	EVENTHANDLER_INVOKE(tcp_offload_listen_stop, tp);
}