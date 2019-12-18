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
 int /*<<< orphan*/  free (struct mbuf*) ; 

__attribute__((used)) static void
free_mbuf_chain(struct mbuf *m)
{
	struct mbuf *next;

	if (m == NULL)
		return;

	next = m->m_next;
	free(m);
	free_mbuf_chain(next);
}