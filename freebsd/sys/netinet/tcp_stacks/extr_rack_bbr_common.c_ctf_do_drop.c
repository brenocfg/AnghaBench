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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

void
ctf_do_drop(struct mbuf *m, struct tcpcb *tp)
{

	/*
	 * Drop space held by incoming segment and return.
	 */
	if (tp != NULL)
		INP_WUNLOCK(tp->t_inpcb);
	if (m)
		m_freem(m);
}