#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct oce_wq {scalar_t__ qstate; int /*<<< orphan*/ * cq; int /*<<< orphan*/  wq_id; int /*<<< orphan*/  parent; } ;
struct oce_mbx {int /*<<< orphan*/  payload; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq_id; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
struct mbx_delete_nic_wq {TYPE_2__ params; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ QCREATED ; 
 scalar_t__ QDELETED ; 
 int /*<<< orphan*/  QTYPE_WQ ; 
 int /*<<< orphan*/  bzero (struct oce_mbx*,int) ; 
 int /*<<< orphan*/  oce_cq_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oce_destroy_q (int /*<<< orphan*/ ,struct oce_mbx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oce_wq_del(struct oce_wq *wq)
{
	struct oce_mbx mbx;
	struct mbx_delete_nic_wq *fwcmd;
	POCE_SOFTC sc = (POCE_SOFTC) wq->parent;

	if (wq->qstate == QCREATED) {
		bzero(&mbx, sizeof(struct oce_mbx));
		/* now fill the command */
		fwcmd = (struct mbx_delete_nic_wq *)&mbx.payload;
		fwcmd->params.req.wq_id = wq->wq_id;
		(void)oce_destroy_q(sc, &mbx,
				sizeof(struct mbx_delete_nic_wq), QTYPE_WQ, 0);
		wq->qstate = QDELETED;
	}

	if (wq->cq != NULL) {
		oce_cq_del(sc, wq->cq);
		wq->cq = NULL;
	}
}