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
struct sge_eq {size_t sidx; int flags; scalar_t__ pidx; scalar_t__ cidx; int /*<<< orphan*/ * desc; } ;
struct sge_txq {int /*<<< orphan*/  r; struct sge_eq eq; } ;
struct sge_qstat {scalar_t__ cidx; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EQ_ENABLED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TXQ_LOCK (struct sge_txq*) ; 
 int /*<<< orphan*/  TXQ_UNLOCK (struct sge_txq*) ; 
 scalar_t__ htobe16 (scalar_t__) ; 
 int /*<<< orphan*/  mp_ring_check_drainage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_ring_is_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
quiesce_txq(struct adapter *sc, struct sge_txq *txq)
{
	struct sge_eq *eq = &txq->eq;
	struct sge_qstat *spg = (void *)&eq->desc[eq->sidx];

	(void) sc;	/* unused */

#ifdef INVARIANTS
	TXQ_LOCK(txq);
	MPASS((eq->flags & EQ_ENABLED) == 0);
	TXQ_UNLOCK(txq);
#endif

	/* Wait for the mp_ring to empty. */
	while (!mp_ring_is_idle(txq->r)) {
		mp_ring_check_drainage(txq->r, 0);
		pause("rquiesce", 1);
	}

	/* Then wait for the hardware to finish. */
	while (spg->cidx != htobe16(eq->pidx))
		pause("equiesce", 1);

	/* Finally, wait for the driver to reclaim all descriptors. */
	while (eq->cidx != eq->pidx)
		pause("dquiesce", 1);
}