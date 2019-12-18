#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct dquot {size_t dq_type; TYPE_1__* dq_ump; scalar_t__ dq_cnt; } ;
struct dqhash {int dummy; } ;
struct TYPE_2__ {struct vnode** um_quotas; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQH_LOCK () ; 
 int /*<<< orphan*/  DQH_UNLOCK () ; 
 int EBUSY ; 
 struct dquot* LIST_FIRST (struct dqhash*) ; 
 struct dquot* LIST_NEXT (struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_hash ; 
 size_t dqhash ; 
 struct dqhash* dqhashtbl ; 

__attribute__((used)) static int
dqflush(struct vnode *vp)
{
	struct dquot *dq, *nextdq;
	struct dqhash *dqh;
	int error;

	/*
	 * Move all dquot's that used to refer to this quota
	 * file off their hash chains (they will eventually
	 * fall off the head of the free list and be re-used).
	 */
	error = 0;
	DQH_LOCK();
	for (dqh = &dqhashtbl[dqhash]; dqh >= dqhashtbl; dqh--) {
		for (dq = LIST_FIRST(dqh); dq; dq = nextdq) {
			nextdq = LIST_NEXT(dq, dq_hash);
			if (dq->dq_ump->um_quotas[dq->dq_type] != vp)
				continue;
			if (dq->dq_cnt)
				error = EBUSY;
			else {
				LIST_REMOVE(dq, dq_hash);
				dq->dq_ump = NULL;
			}
		}
	}
	DQH_UNLOCK();
	return (error);
}