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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct llentry {struct mbuf* la_hold; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void 
clear_llinfo_pqueue(struct llentry *ln)
{
	struct mbuf *m_hold, *m_hold_next;

	for (m_hold = ln->la_hold; m_hold; m_hold = m_hold_next) {
		m_hold_next = m_hold->m_nextpkt;
		m_freem(m_hold);
	}

	ln->la_hold = NULL;
}