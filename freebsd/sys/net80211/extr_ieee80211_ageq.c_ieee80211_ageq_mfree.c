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
 int /*<<< orphan*/  ageq_mfree (struct mbuf*) ; 

void
ieee80211_ageq_mfree(struct mbuf *m)
{
	struct mbuf *next;

	for (; m != NULL; m = next) {
		next = m->m_nextpkt;
		ageq_mfree(m);
	}
}