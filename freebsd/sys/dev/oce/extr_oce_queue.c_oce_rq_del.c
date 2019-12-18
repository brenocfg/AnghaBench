#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct oce_rq {scalar_t__ qstate; int /*<<< orphan*/ * cq; int /*<<< orphan*/  rq_id; int /*<<< orphan*/  islro; int /*<<< orphan*/  parent; } ;
struct oce_mbx {int /*<<< orphan*/  payload; } ;
struct TYPE_7__ {int rq_flags; int /*<<< orphan*/  rq_id; } ;
struct TYPE_8__ {TYPE_3__ req; } ;
struct mbx_delete_nic_rq_v1 {TYPE_4__ params; } ;
struct TYPE_5__ {int /*<<< orphan*/  rq_id; } ;
struct TYPE_6__ {TYPE_1__ req; } ;
struct mbx_delete_nic_rq {TYPE_2__ params; } ;
typedef  int /*<<< orphan*/  mbx ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int NIC_RQ_FLAGS_LRO ; 
 int NIC_RQ_FLAGS_RSS ; 
 scalar_t__ QCREATED ; 
 scalar_t__ QDELETED ; 
 int /*<<< orphan*/  QTYPE_RQ ; 
 int /*<<< orphan*/  bzero (struct oce_mbx*,int) ; 
 int /*<<< orphan*/  oce_cq_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oce_destroy_q (int /*<<< orphan*/ ,struct oce_mbx*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
oce_rq_del(struct oce_rq *rq)
{
	POCE_SOFTC sc = (POCE_SOFTC) rq->parent;
	struct oce_mbx mbx;
	struct mbx_delete_nic_rq *fwcmd;
	struct mbx_delete_nic_rq_v1 *fwcmd1;

	if (rq->qstate == QCREATED) {
		bzero(&mbx, sizeof(mbx));
		if(!rq->islro) {
			fwcmd = (struct mbx_delete_nic_rq *)&mbx.payload;
			fwcmd->params.req.rq_id = rq->rq_id;
			(void)oce_destroy_q(sc, &mbx, sizeof(struct mbx_delete_nic_rq), QTYPE_RQ, 0);
		}else {
			fwcmd1 = (struct mbx_delete_nic_rq_v1 *)&mbx.payload;
			fwcmd1->params.req.rq_id = rq->rq_id;
			fwcmd1->params.req.rq_flags = (NIC_RQ_FLAGS_RSS | NIC_RQ_FLAGS_LRO);
			(void)oce_destroy_q(sc, &mbx, sizeof(struct mbx_delete_nic_rq_v1), QTYPE_RQ, 1);
		}
		rq->qstate = QDELETED;
	}

	if (rq->cq != NULL) {
		oce_cq_del(sc, rq->cq);
		rq->cq = NULL;
	}
}