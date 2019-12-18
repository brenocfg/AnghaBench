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
struct mbuf {struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_free (struct mbuf*) ; 

__attribute__((used)) static void
m_freem(struct mbuf *m0)
{
	struct mbuf *m;

	while (m0) {
		m = m0->m_next;
		m_free(m0);
		m0 = m;
	}
}