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
struct vnode {int dummy; } ;
struct dquot {int dq_cnt; int dq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQH_LOCK () ; 
 int /*<<< orphan*/  DQH_UNLOCK () ; 
 int DQ_MOD ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct dquot* NODQUOT ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_freelist ; 
 int /*<<< orphan*/  dqfreelist ; 
 int /*<<< orphan*/  dqsync (struct vnode*,struct dquot*) ; 

void
dqrele(struct vnode *vp, struct dquot *dq)
{

	if (dq == NODQUOT)
		return;
	DQH_LOCK();
	KASSERT(dq->dq_cnt > 0, ("Lost dq %p reference 1", dq));
	if (dq->dq_cnt > 1) {
		dq->dq_cnt--;
		DQH_UNLOCK();
		return;
	}
	DQH_UNLOCK();
sync:
	(void) dqsync(vp, dq);

	DQH_LOCK();
	KASSERT(dq->dq_cnt > 0, ("Lost dq %p reference 2", dq));
	if (--dq->dq_cnt > 0)
	{
		DQH_UNLOCK();
		return;
	}

	/*
	 * The dq may become dirty after it is synced but before it is
	 * put to the free list. Checking the DQ_MOD there without
	 * locking dq should be safe since no other references to the
	 * dq exist.
	 */
	if ((dq->dq_flags & DQ_MOD) != 0) {
		dq->dq_cnt++;
		DQH_UNLOCK();
		goto sync;
	}
	TAILQ_INSERT_TAIL(&dqfreelist, dq, dq_freelist);
	DQH_UNLOCK();
}