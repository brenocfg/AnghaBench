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
struct mbuf {int m_len; int /*<<< orphan*/ * m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 struct mbuf* m_getptr (struct mbuf*,int,int*) ; 

__attribute__((used)) static void
m_trim(struct mbuf *m, int len)
{
	struct mbuf *n;
	int off;

	if (m == NULL)
		return;
	n = m_getptr(m, len, &off);
	if (n) {
		n->m_len = off;
		if (n->m_next) {
			m_freem(n->m_next);
			n->m_next = NULL;
		}
	}
}