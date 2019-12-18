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
typedef  scalar_t__ uint32_t ;
struct ccp_queue {int cq_tail; scalar_t__ desc_ring_bus_addr; int /*<<< orphan*/  cq_qindex; int /*<<< orphan*/  cq_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_Q_TAIL_LO_BASE ; 
 int Q_DESC_SIZE ; 
 int /*<<< orphan*/  ccp_write_queue_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
ccp_queue_write_tail(struct ccp_queue *qp)
{
	ccp_write_queue_4(qp->cq_softc, qp->cq_qindex, CMD_Q_TAIL_LO_BASE,
	    ((uint32_t)qp->desc_ring_bus_addr) + (Q_DESC_SIZE * qp->cq_tail));
}