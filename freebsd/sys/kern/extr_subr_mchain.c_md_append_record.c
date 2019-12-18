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
struct mdchain {struct mbuf* md_top; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  md_initm (struct mdchain*,struct mbuf*) ; 

void
md_append_record(struct mdchain *mdp, struct mbuf *top)
{
	struct mbuf *m;

	if (mdp->md_top == NULL) {
		md_initm(mdp, top);
		return;
	}
	m = mdp->md_top;
	while (m->m_nextpkt)
		m = m->m_nextpkt;
	m->m_nextpkt = top;
	top->m_nextpkt = NULL;
	return;
}