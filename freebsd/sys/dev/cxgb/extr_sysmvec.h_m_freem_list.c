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

/* Variables and functions */
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  prefetch (struct mbuf*) ; 

__attribute__((used)) static __inline void
m_freem_list(struct mbuf *m)
{
	struct mbuf *n; 

	while (m != NULL) {
		n = m->m_nextpkt;
		if (n != NULL)
			prefetch(n);
		m_freem(m);
		m = n;
	}	
}