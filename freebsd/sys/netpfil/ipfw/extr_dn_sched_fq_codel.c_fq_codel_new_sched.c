#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct dn_queue {int /*<<< orphan*/  fs; struct dn_sch_inst* _si; TYPE_1__ ni; } ;
struct fq_codel_si {TYPE_5__* flows; int /*<<< orphan*/  oldflows; int /*<<< orphan*/  newflows; int /*<<< orphan*/  perturbation; struct dn_queue main_q; } ;
struct TYPE_9__ {int flows_cnt; } ;
struct fq_codel_schk {TYPE_3__ cfg; } ;
struct fq_codel_flow {int dummy; } ;
struct dn_sch_inst {TYPE_2__* sched; } ;
struct TYPE_12__ {int /*<<< orphan*/  ref_count; } ;
struct TYPE_10__ {int maxpkt_size; } ;
struct TYPE_11__ {TYPE_4__ cst; } ;
struct TYPE_8__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*) ; 
 int /*<<< orphan*/  DN_QUEUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_6__ fq_codel_desc ; 
 TYPE_5__* mallocarray (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/  set_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fq_codel_new_sched(struct dn_sch_inst *_si)
{
	struct fq_codel_si *si;
	struct dn_queue *q;
	struct fq_codel_schk *schk;
	int i;

	si = (struct fq_codel_si *)_si;
	schk = (struct fq_codel_schk *)(_si->sched+1);

	if(si->flows) {
		D("si already configured!");
		return 0;
	}

	/* init the main queue */
	q = &si->main_q;
	set_oid(&q->ni.oid, DN_QUEUE, sizeof(*q));
	q->_si = _si;
	q->fs = _si->sched->fs;

	/* allocate memory for flows array */
	si->flows = mallocarray(schk->cfg.flows_cnt,
	    sizeof(struct fq_codel_flow), M_DUMMYNET, M_NOWAIT | M_ZERO);
	if (si->flows == NULL) {
		D("cannot allocate memory for fq_codel configuration parameters");
		return ENOMEM ; 
	}

	/* init perturbation for this si */
	si->perturbation = random();

	/* init the old and new flows lists */
	STAILQ_INIT(&si->newflows);
	STAILQ_INIT(&si->oldflows);

	/* init the flows (sub-queues) */
	for (i = 0; i < schk->cfg.flows_cnt; i++) {
		/* init codel */
		si->flows[i].cst.maxpkt_size = 500;
	}

	fq_codel_desc.ref_count++;
	return 0;
}