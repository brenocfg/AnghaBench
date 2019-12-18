#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  if_id; } ;
struct oce_rq {TYPE_2__* ring; scalar_t__ qstate; TYPE_1__ cfg; struct oce_cq* cq; TYPE_3__* parent; } ;
struct oce_nic_rx_cqe {int dummy; } ;
struct oce_eq {size_t cq_valid; struct oce_cq** cq; } ;
struct oce_cq {int /*<<< orphan*/  cq_handler; struct oce_rq* cb_arg; } ;
struct TYPE_7__ {scalar_t__ enable_hwlro; } ;
struct TYPE_6__ {scalar_t__ pidx; scalar_t__ cidx; } ;
typedef  TYPE_3__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_LEN_1024 ; 
 int /*<<< orphan*/  CQ_LEN_2048 ; 
 int ENXIO ; 
 struct oce_cq* oce_cq_create (TYPE_3__*,struct oce_eq*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oce_rq_handler ; 

__attribute__((used)) static int
oce_rq_create(struct oce_rq *rq, uint32_t if_id, struct oce_eq *eq)
{
	POCE_SOFTC sc = rq->parent;
	struct oce_cq *cq;

	cq = oce_cq_create(sc, eq,
		       	sc->enable_hwlro ? CQ_LEN_2048 : CQ_LEN_1024,
			sizeof(struct oce_nic_rx_cqe), 0, 1, 0, 3);		
			
	if (!cq)
		return ENXIO;

	rq->cq = cq;
	rq->cfg.if_id = if_id;

	/* Dont create RQ here. Create in if_activate */
	rq->qstate     = 0;
	rq->ring->cidx = 0;
	rq->ring->pidx = 0;
	eq->cq[eq->cq_valid] = cq;
	eq->cq_valid++;
	cq->cb_arg = rq;
	cq->cq_handler = oce_rq_handler;

	return 0;

}