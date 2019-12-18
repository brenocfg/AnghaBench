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
struct tcpcb {int /*<<< orphan*/  t_flags2; int /*<<< orphan*/  t_logstate; int /*<<< orphan*/  t_logs; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TF2_LOG_AUTO ; 
 int /*<<< orphan*/  tcp_log_auto_mode ; 
 scalar_t__ tcp_log_selectauto () ; 

void
tcp_log_tcpcbinit(struct tcpcb *tp)
{

	/* A new TCPCB should start out zero-initialized. */
	STAILQ_INIT(&tp->t_logs);

	/*
	 * If we are doing auto-capturing, figure out whether we will capture
	 * this session.
	 */
	if (tcp_log_selectauto()) {
		tp->t_logstate = tcp_log_auto_mode;
		tp->t_flags2 |= TF2_LOG_AUTO;
	}
}