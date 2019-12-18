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
struct mq {struct mbuf* head; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct dn_sch_inst {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct mbuf *
default_dequeue(struct dn_sch_inst *si)
{
	struct mq *mq = (struct mq *)si;
	struct mbuf *m;
	/* this is the default function if no scheduler is provided */
	if ((m = mq->head)) {
		m = mq->head;
		mq->head = m->m_nextpkt;
		m->m_nextpkt = NULL;
	}
	return m;
}