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
struct mbufq {struct mbuf* head; struct mbuf* tail; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */

__attribute__((used)) static struct mbuf *
mbufq_dequeue(struct mbufq *q)
{
	struct mbuf *m;

	m = q->head;
	if (m) {
		if (q->tail == m)
			q->tail = NULL;
		q->head = m->m_nextpkt;
		m->m_nextpkt = NULL;
	}
	return (m);
}