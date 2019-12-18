#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct mq {struct mbuf* head; } ;
struct TYPE_9__ {int len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct TYPE_10__ {int bandwidth; int delay; } ;
struct dn_schk {TYPE_3__ link; TYPE_1__* fp; } ;
struct TYPE_12__ {int /*<<< orphan*/ * head; } ;
struct TYPE_11__ {TYPE_5__ mq; } ;
struct dn_sch_inst {scalar_t__ credit; int sched_time; int idle_time; TYPE_4__ dline; int /*<<< orphan*/  kflags; struct dn_schk* sched; } ;
struct TYPE_14__ {int curr_time; int /*<<< orphan*/  evheap; } ;
struct TYPE_13__ {int output_time; } ;
struct TYPE_8__ {struct mbuf* (* dequeue ) (struct dn_sch_inst*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DN_ACTIVE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int div64 (scalar_t__,int) ; 
 TYPE_7__ dn_cfg ; 
 TYPE_6__* dn_tag_get (struct mbuf*) ; 
 int extra_bits (struct mbuf*,struct dn_schk*) ; 
 int /*<<< orphan*/  heap_insert (int /*<<< orphan*/ *,int,struct dn_sch_inst*) ; 
 int hz ; 
 int /*<<< orphan*/  mq_append (TYPE_5__*,struct mbuf*) ; 
 struct mbuf* stub1 (struct dn_sch_inst*) ; 
 int /*<<< orphan*/  transmit_event (struct mq*,TYPE_4__*,int) ; 

__attribute__((used)) static struct mbuf *
serve_sched(struct mq *q, struct dn_sch_inst *si, uint64_t now)
{
	struct mq def_q;
	struct dn_schk *s = si->sched;
	struct mbuf *m = NULL;
	int delay_line_idle = (si->dline.mq.head == NULL);
	int done, bw;

	if (q == NULL) {
		q = &def_q;
		q->head = NULL;
	}

	bw = s->link.bandwidth;
	si->kflags &= ~DN_ACTIVE;

	if (bw > 0)
		si->credit += (now - si->sched_time) * bw;
	else
		si->credit = 0;
	si->sched_time = now;
	done = 0;
	while (si->credit >= 0 && (m = s->fp->dequeue(si)) != NULL) {
		uint64_t len_scaled;

		done++;
		len_scaled = (bw == 0) ? 0 : hz *
			(m->m_pkthdr.len * 8 + extra_bits(m, s));
		si->credit -= len_scaled;
		/* Move packet in the delay line */
		dn_tag_get(m)->output_time = dn_cfg.curr_time + s->link.delay ;
		mq_append(&si->dline.mq, m);
	}

	/*
	 * If credit >= 0 the instance is idle, mark time.
	 * Otherwise put back in the heap, and adjust the output
	 * time of the last inserted packet, m, which was too early.
	 */
	if (si->credit >= 0) {
		si->idle_time = now;
	} else {
		uint64_t t;
		KASSERT (bw > 0, ("bw=0 and credit<0 ?"));
		t = div64(bw - 1 - si->credit, bw);
		if (m)
			dn_tag_get(m)->output_time += t;
		si->kflags |= DN_ACTIVE;
		heap_insert(&dn_cfg.evheap, now + t, si);
	}
	if (delay_line_idle && done)
		transmit_event(q, &si->dline, now);
	return q->head;
}