#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct mbuf {int /*<<< orphan*/ * m_nextpkt; } ;
struct m_tag {scalar_t__ m_tag_id; int /*<<< orphan*/  m_tag_cookie; } ;
struct TYPE_6__ {int info; } ;
struct ip_fw_args {int flags; int /*<<< orphan*/  f_id; TYPE_1__ rule; } ;
struct dn_sch_inst {int kflags; scalar_t__ idle_time; scalar_t__ sched_time; scalar_t__ credit; } ;
struct dn_queue {int dummy; } ;
struct dn_link {scalar_t__ bandwidth; scalar_t__ burst; } ;
struct TYPE_8__ {int flags; } ;
struct dn_fsk {TYPE_3__ fs; TYPE_4__* sched; } ;
struct TYPE_10__ {scalar_t__ curr_time; scalar_t__ io_fast; int /*<<< orphan*/  fshash; int /*<<< orphan*/  pending; scalar_t__ busy; } ;
struct TYPE_9__ {struct dn_link link; TYPE_2__* fp; } ;
struct TYPE_7__ {int flags; scalar_t__ (* enqueue ) (struct dn_sch_inst*,struct dn_queue*,struct mbuf*) ;} ;

/* Variables and functions */
 int DIR_IN ; 
 int DIR_OUT ; 
 int DN_ACTIVE ; 
 int /*<<< orphan*/  DN_BH_WLOCK () ; 
 int /*<<< orphan*/  DN_BH_WUNLOCK () ; 
 int DN_MAX_ID ; 
 int DN_MULTIQUEUE ; 
 int DN_NOERROR ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  FREE_PKT (struct mbuf*) ; 
 int IPFW_ARGS_ETHER ; 
 int IPFW_ARGS_IN ; 
 int IPFW_ARGS_IP6 ; 
 int IPFW_INFO_MASK ; 
 int IPFW_IS_PIPE ; 
 int /*<<< orphan*/  MTAG_IPFW_RULE ; 
 int PROTO_IPV6 ; 
 int PROTO_LAYER2 ; 
 TYPE_5__ dn_cfg ; 
 struct dn_fsk* dn_ht_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummynet_send (struct mbuf*) ; 
 int /*<<< orphan*/  io_pkt ; 
 int /*<<< orphan*/  io_pkt_drop ; 
 int /*<<< orphan*/  io_pkt_fast ; 
 struct dn_queue* ipdn_q_find (struct dn_fsk*,struct dn_sch_inst*,int /*<<< orphan*/ *) ; 
 struct dn_sch_inst* ipdn_si_find (TYPE_4__*,int /*<<< orphan*/ *) ; 
 struct m_tag* m_tag_first (struct mbuf*) ; 
 int /*<<< orphan*/  mq_append (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct mbuf* serve_sched (int /*<<< orphan*/ *,struct dn_sch_inst*,scalar_t__) ; 
 scalar_t__ stub1 (struct dn_sch_inst*,struct dn_queue*,struct mbuf*) ; 
 scalar_t__ tag_mbuf (struct mbuf*,int,struct ip_fw_args*) ; 

int
dummynet_io(struct mbuf **m0, struct ip_fw_args *fwa)
{
	struct mbuf *m = *m0;
	struct dn_fsk *fs = NULL;
	struct dn_sch_inst *si;
	struct dn_queue *q = NULL;	/* default */
	int fs_id, dir;

	fs_id = (fwa->rule.info & IPFW_INFO_MASK) +
		((fwa->rule.info & IPFW_IS_PIPE) ? 2*DN_MAX_ID : 0);
	/* XXXGL: convert args to dir */
	if (fwa->flags & IPFW_ARGS_IN)
		dir = DIR_IN;
	else
		dir = DIR_OUT;
	if (fwa->flags & IPFW_ARGS_ETHER)
		dir |= PROTO_LAYER2;
	else if (fwa->flags & IPFW_ARGS_IP6)
		dir |= PROTO_IPV6;
	DN_BH_WLOCK();
	io_pkt++;
	/* we could actually tag outside the lock, but who cares... */
	if (tag_mbuf(m, dir, fwa))
		goto dropit;
	if (dn_cfg.busy) {
		/* if the upper half is busy doing something expensive,
		 * lets queue the packet and move forward
		 */
		mq_append(&dn_cfg.pending, m);
		m = *m0 = NULL; /* consumed */
		goto done; /* already active, nothing to do */
	}
	/* XXX locate_flowset could be optimised with a direct ref. */
	fs = dn_ht_find(dn_cfg.fshash, fs_id, 0, NULL);
	if (fs == NULL)
		goto dropit;	/* This queue/pipe does not exist! */
	if (fs->sched == NULL)	/* should not happen */
		goto dropit;
	/* find scheduler instance, possibly applying sched_mask */
	si = ipdn_si_find(fs->sched, &(fwa->f_id));
	if (si == NULL)
		goto dropit;
	/*
	 * If the scheduler supports multiple queues, find the right one
	 * (otherwise it will be ignored by enqueue).
	 */
	if (fs->sched->fp->flags & DN_MULTIQUEUE) {
		q = ipdn_q_find(fs, si, &(fwa->f_id));
		if (q == NULL)
			goto dropit;
	}
	if (fs->sched->fp->enqueue(si, q, m)) {
		/* packet was dropped by enqueue() */
		m = *m0 = NULL;

		/* dn_enqueue already increases io_pkt_drop */
		io_pkt_drop--;

		goto dropit;
	}

	if (si->kflags & DN_ACTIVE) {
		m = *m0 = NULL; /* consumed */
		goto done; /* already active, nothing to do */
	}

	/* compute the initial allowance */
	if (si->idle_time < dn_cfg.curr_time) {
	    /* Do this only on the first packet on an idle pipe */
	    struct dn_link *p = &fs->sched->link;

	    si->sched_time = dn_cfg.curr_time;
	    si->credit = dn_cfg.io_fast ? p->bandwidth : 0;
	    if (p->burst) {
		uint64_t burst = (dn_cfg.curr_time - si->idle_time) * p->bandwidth;
		if (burst > p->burst)
			burst = p->burst;
		si->credit += burst;
	    }
	}
	/* pass through scheduler and delay line */
	m = serve_sched(NULL, si, dn_cfg.curr_time);

	/* optimization -- pass it back to ipfw for immediate send */
	/* XXX Don't call dummynet_send() if scheduler return the packet
	 *     just enqueued. This avoid a lock order reversal.
	 *     
	 */
	if (/*dn_cfg.io_fast &&*/ m == *m0 && (dir & PROTO_LAYER2) == 0 ) {
		/* fast io, rename the tag * to carry reinject info. */
		struct m_tag *tag = m_tag_first(m);

		tag->m_tag_cookie = MTAG_IPFW_RULE;
		tag->m_tag_id = 0;
		io_pkt_fast++;
		if (m->m_nextpkt != NULL) {
			printf("dummynet: fast io: pkt chain detected!\n");
			m->m_nextpkt = NULL;
		}
		m = NULL;
	} else {
		*m0 = NULL;
	}
done:
	DN_BH_WUNLOCK();
	if (m)
		dummynet_send(m);
	return 0;

dropit:
	io_pkt_drop++;
	DN_BH_WUNLOCK();
	if (m)
		FREE_PKT(m);
	*m0 = NULL;
	return (fs && (fs->fs.flags & DN_NOERROR)) ? 0 : ENOBUFS;
}