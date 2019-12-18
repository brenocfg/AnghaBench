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
struct mbuf {int m_flags; struct mbuf* m_next; } ;

/* Variables and functions */
 int M_NOTREADY ; 
 int M_PROTOFLAGS ; 
 int PRUS_NOTREADY ; 

__attribute__((used)) static void
sbm_clrprotoflags(struct mbuf *m, int flags)
{
	int mask;

	mask = ~M_PROTOFLAGS;
	if (flags & PRUS_NOTREADY)
		mask |= M_NOTREADY;
	while (m) {
		m->m_flags &= mask;
		m = m->m_next;
	}
}