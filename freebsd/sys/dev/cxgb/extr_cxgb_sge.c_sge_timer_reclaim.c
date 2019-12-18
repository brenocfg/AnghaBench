#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mtx {int dummy; } ;
struct TYPE_11__ {int cntxt_id; scalar_t__ credits; struct mtx lock; } ;
struct sge_qset {TYPE_6__ rspq; TYPE_8__* fl; } ;
struct port_info {int nqsets; int first_qset; TYPE_2__* adapter; } ;
struct TYPE_9__ {struct sge_qset* qs; } ;
struct TYPE_10__ {int flags; TYPE_1__ sge; } ;
typedef  TYPE_2__ adapter_t ;
struct TYPE_12__ {int credits; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_RSPQ_FL_STATUS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TXQ_OFLD ; 
 int USING_MSIX ; 
 int /*<<< orphan*/  __refill_fl (TYPE_2__*,TYPE_8__*) ; 
 scalar_t__ mtx_trylock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct sge_qset*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refill_rspq (TYPE_2__*,TYPE_6__*,int) ; 
 int t3_read_reg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sge_timer_reclaim(void *arg, int ncount)
{
	struct port_info *pi = arg;
	int i, nqsets = pi->nqsets;
	adapter_t *sc = pi->adapter;
	struct sge_qset *qs;
	struct mtx *lock;
	
	KASSERT((sc->flags & USING_MSIX) == 0,
	    ("can't call timer reclaim for msi-x"));

	for (i = 0; i < nqsets; i++) {
		qs = &sc->sge.qs[pi->first_qset + i];

		reclaim_completed_tx(qs, 16, TXQ_OFLD);
		lock = (sc->flags & USING_MSIX) ? &qs->rspq.lock :
			    &sc->sge.qs[0].rspq.lock;

		if (mtx_trylock(lock)) {
			/* XXX currently assume that we are *NOT* polling */
			uint32_t status = t3_read_reg(sc, A_SG_RSPQ_FL_STATUS);

			if (qs->fl[0].credits < qs->fl[0].size - 16)
				__refill_fl(sc, &qs->fl[0]);
			if (qs->fl[1].credits < qs->fl[1].size - 16)
				__refill_fl(sc, &qs->fl[1]);
			
			if (status & (1 << qs->rspq.cntxt_id)) {
				if (qs->rspq.credits) {
					refill_rspq(sc, &qs->rspq, 1);
					qs->rspq.credits--;
					t3_write_reg(sc, A_SG_RSPQ_FL_STATUS, 
					    1 << qs->rspq.cntxt_id);
				}
			}
			mtx_unlock(lock);
		}
	}
}