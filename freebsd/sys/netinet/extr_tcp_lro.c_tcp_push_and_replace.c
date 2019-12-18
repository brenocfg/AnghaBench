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
struct tcpcb {int dummy; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct lro_entry {TYPE_1__* m_head; } ;
struct lro_ctrl {int dummy; } ;
struct TYPE_2__ {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_flush_out_le (struct tcpcb*,struct lro_ctrl*,struct lro_entry*,int) ; 
 int /*<<< orphan*/  tcp_set_le_to_m (struct lro_ctrl*,struct lro_entry*,struct mbuf*) ; 

__attribute__((used)) static void
tcp_push_and_replace(struct tcpcb *tp, struct lro_ctrl *lc, struct lro_entry *le, struct mbuf *m, int locked)
{
	/*
	 * Push up the stack the current le and replace
	 * it with m. 
	 */
	struct mbuf *msave;

	/* Grab off the next and save it */
	msave = le->m_head->m_nextpkt;
	le->m_head->m_nextpkt = NULL;
	/* Now push out the old le entry */
	tcp_flush_out_le(tp, lc, le, locked);
	/*
	 * Now to replace the data properly in the le 
	 * we have to reset the tcp header and
	 * other fields.
	 */
	tcp_set_le_to_m(lc, le, m);
	/* Restore the next list */
	m->m_nextpkt = msave;
}