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
struct TYPE_11__ {scalar_t__ head; } ;
struct dn_queue {TYPE_5__ mq; TYPE_4__* _si; struct dn_fsk* fs; } ;
struct dn_fsk {TYPE_3__* sched; TYPE_1__* aqmfp; } ;
struct TYPE_12__ {int /*<<< orphan*/  queue_count; } ;
struct TYPE_10__ {int /*<<< orphan*/  q_count; } ;
struct TYPE_9__ {TYPE_2__* fp; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* free_queue ) (struct dn_queue*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* cleanup ) (struct dn_queue*) ;} ;

/* Variables and functions */
 int DN_DESTROY ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 int /*<<< orphan*/  bzero (struct dn_queue*,int) ; 
 TYPE_6__ dn_cfg ; 
 int /*<<< orphan*/  dn_free_pkts (scalar_t__) ; 
 int /*<<< orphan*/  free (struct dn_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dn_queue*) ; 
 int /*<<< orphan*/  stub2 (struct dn_queue*) ; 

__attribute__((used)) static void
dn_delete_queue(struct dn_queue *q, int flags)
{
	struct dn_fsk *fs = q->fs;

#ifdef NEW_AQM
	/* clean up AQM status for queue 'q'
	 * cleanup here is called just with MULTIQUEUE
	 */
	if (fs && fs->aqmfp && fs->aqmfp->cleanup)
		fs->aqmfp->cleanup(q);
#endif
	// D("fs %p si %p\n", fs, q->_si);
	/* notify the parent scheduler that the queue is going away */
	if (fs && fs->sched->fp->free_queue)
		fs->sched->fp->free_queue(q);
	q->_si->q_count--;
	q->_si = NULL;
	if (flags & DN_DESTROY) {
		if (q->mq.head)
			dn_free_pkts(q->mq.head);
		bzero(q, sizeof(*q));	// safety
		free(q, M_DUMMYNET);
		dn_cfg.queue_count--;
	}
}