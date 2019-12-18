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
struct ccp_softc {int ring_size_order; } ;
struct ccp_queue {int cq_waiting; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  cq_tail; struct ccp_softc* cq_softc; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int M_WAITOK ; 
 unsigned int ccp_queue_get_ring_space (struct ccp_queue*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccp_queue_reserve_space(struct ccp_queue *qp, unsigned n, int mflags)
{
	struct ccp_softc *sc;

	mtx_assert(&qp->cq_lock, MA_OWNED);
	sc = qp->cq_softc;

	if (n < 1 || n >= (1 << sc->ring_size_order))
		return (EINVAL);

	while (true) {
		if (ccp_queue_get_ring_space(qp) >= n)
			return (0);
		if ((mflags & M_WAITOK) == 0)
			return (EAGAIN);
		qp->cq_waiting = true;
		msleep(&qp->cq_tail, &qp->cq_lock, 0, "ccpqfull", 0);
	}
}