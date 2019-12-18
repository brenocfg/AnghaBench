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
struct TYPE_5__ {int /*<<< orphan*/  q_len; } ;
struct oce_wq {TYPE_2__* ring; TYPE_1__ cfg; int /*<<< orphan*/  wq_free; int /*<<< orphan*/  qstate; struct oce_cq* cq; TYPE_3__* parent; } ;
struct oce_nic_tx_cqe {int dummy; } ;
struct oce_eq {size_t cq_valid; struct oce_cq** cq; } ;
struct oce_cq {int /*<<< orphan*/  cq_handler; struct oce_wq* cb_arg; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ pidx; scalar_t__ cidx; } ;
typedef  TYPE_3__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_LEN_1024 ; 
 int ENXIO ; 
 int /*<<< orphan*/  QCREATED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct oce_cq* oce_cq_create (TYPE_3__*,struct oce_eq*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int oce_mbox_create_wq (struct oce_wq*) ; 
 int /*<<< orphan*/  oce_wq_del (struct oce_wq*) ; 
 int /*<<< orphan*/  oce_wq_handler ; 

__attribute__((used)) static int
oce_wq_create(struct oce_wq *wq, struct oce_eq *eq)
{
	POCE_SOFTC sc = wq->parent;
	struct oce_cq *cq;
	int rc = 0;

	/* create the CQ */
	cq = oce_cq_create(sc,
			   eq,
			   CQ_LEN_1024,
			   sizeof(struct oce_nic_tx_cqe), 0, 1, 0, 3);
	if (!cq)
		return ENXIO;


	wq->cq = cq;

	rc = oce_mbox_create_wq(wq);
	if (rc)
		goto error;

	wq->qstate = QCREATED;
	wq->wq_free = wq->cfg.q_len;
	wq->ring->cidx = 0;
	wq->ring->pidx = 0;

	eq->cq[eq->cq_valid] = cq;
	eq->cq_valid++;
	cq->cb_arg = wq;
	cq->cq_handler = oce_wq_handler;

	return 0;

error:
	device_printf(sc->dev, "WQ create failed\n");
	oce_wq_del(wq);
	return rc;
}