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

void
ieee80211_free_mbuf(struct mbuf *m)
{
	struct mbuf *next;

	if (m == NULL)
		return;

	do {
		next = m->m_nextpkt;
		m->m_nextpkt = NULL;
		m_freem(m);
	} while ((m = next) != NULL);
}