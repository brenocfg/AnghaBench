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
struct ccp_queue {int cq_tail; int cq_head; struct ccp_softc* cq_softc; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned
ccp_queue_get_active(struct ccp_queue *qp)
{
	struct ccp_softc *sc;

	sc = qp->cq_softc;
	return ((qp->cq_tail - qp->cq_head) & ((1 << sc->ring_size_order) - 1));
}