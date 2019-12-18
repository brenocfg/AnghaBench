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
struct tcpcb {int t_logstate; int /*<<< orphan*/  t_flags2; int /*<<< orphan*/  t_logs; int /*<<< orphan*/  t_inpcb; } ;
struct tcp_log_mem {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 struct tcp_log_mem* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
#define  TCP_LOG_STATE_CLEAR 134 
#define  TCP_LOG_STATE_CONTINUAL 133 
#define  TCP_LOG_STATE_HEAD 132 
#define  TCP_LOG_STATE_HEAD_AUTO 131 
#define  TCP_LOG_STATE_OFF 130 
#define  TCP_LOG_STATE_TAIL 129 
#define  TCP_LOG_STATE_TAIL_AUTO 128 
 int /*<<< orphan*/  TF2_LOG_AUTO ; 
 int /*<<< orphan*/  tcp_log_remove_log_head (struct tcpcb*,struct tcp_log_mem*) ; 

int
tcp_log_state_change(struct tcpcb *tp, int state)
{
	struct tcp_log_mem *log_entry;

	INP_WLOCK_ASSERT(tp->t_inpcb);
	switch(state) {
	case TCP_LOG_STATE_CLEAR:
		while ((log_entry = STAILQ_FIRST(&tp->t_logs)) != NULL)
			tcp_log_remove_log_head(tp, log_entry);
		/* Fall through */

	case TCP_LOG_STATE_OFF:
		tp->t_logstate = TCP_LOG_STATE_OFF;
		break;

	case TCP_LOG_STATE_TAIL:
	case TCP_LOG_STATE_HEAD:
	case TCP_LOG_STATE_CONTINUAL:
	case TCP_LOG_STATE_HEAD_AUTO:
	case TCP_LOG_STATE_TAIL_AUTO:
		tp->t_logstate = state;
		break;

	default:
		return (EINVAL);
	}

	tp->t_flags2 &= ~(TF2_LOG_AUTO);

	return (0);
}