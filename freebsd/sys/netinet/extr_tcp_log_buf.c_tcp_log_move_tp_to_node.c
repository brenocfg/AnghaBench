#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcpcb {scalar_t__ t_lognum; int /*<<< orphan*/  t_logs; int /*<<< orphan*/  t_lib; TYPE_2__* t_inpcb; } ;
struct tcp_log_id_node {int /*<<< orphan*/  tln_bucket; scalar_t__ tln_count; int /*<<< orphan*/  tln_entries; int /*<<< orphan*/  tln_af; int /*<<< orphan*/  tln_ie; } ;
struct TYPE_3__ {int inc_flags; int /*<<< orphan*/  inc_ie; } ;
struct TYPE_4__ {TYPE_1__ inp_inc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int INC_ISIPV6 ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tcp_log_move_tp_to_node(struct tcpcb *tp, struct tcp_log_id_node *tln)
{

	INP_WLOCK_ASSERT(tp->t_inpcb);

	tln->tln_ie = tp->t_inpcb->inp_inc.inc_ie;
	if (tp->t_inpcb->inp_inc.inc_flags & INC_ISIPV6)
		tln->tln_af = AF_INET6;
	else
		tln->tln_af = AF_INET;
	tln->tln_entries = tp->t_logs;
	tln->tln_count = tp->t_lognum;
	tln->tln_bucket = tp->t_lib;

	/* Clear information from the PCB. */
	STAILQ_INIT(&tp->t_logs);
	tp->t_lognum = 0;
}