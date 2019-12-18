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
struct oce_mq {scalar_t__ qstate; int /*<<< orphan*/ * cq; int /*<<< orphan*/  mq_id; int /*<<< orphan*/ * ring; int /*<<< orphan*/  parent; } ;
struct oce_mbx {int /*<<< orphan*/  payload; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
struct mbx_destroy_common_mq {TYPE_2__ params; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ QCREATED ; 
 scalar_t__ QDELETED ; 
 int /*<<< orphan*/  QTYPE_MQ ; 
 int /*<<< orphan*/  bzero (struct oce_mbx*,int) ; 
 int /*<<< orphan*/  free (struct oce_mq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_cq_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oce_destroy_q (int /*<<< orphan*/ ,struct oce_mbx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_destroy_ring_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
oce_mq_free(struct oce_mq *mq)
{
	POCE_SOFTC sc = (POCE_SOFTC) mq->parent;
	struct oce_mbx mbx;
	struct mbx_destroy_common_mq *fwcmd;

	if (!mq)
		return;

	if (mq->ring != NULL) {
		oce_destroy_ring_buffer(sc, mq->ring);
		mq->ring = NULL;
		if (mq->qstate == QCREATED) {
			bzero(&mbx, sizeof (struct oce_mbx));
			fwcmd = (struct mbx_destroy_common_mq *)&mbx.payload;
			fwcmd->params.req.id = mq->mq_id;
			(void) oce_destroy_q(sc, &mbx,
				sizeof (struct mbx_destroy_common_mq),
				QTYPE_MQ, 0);
		}
		mq->qstate = QDELETED;
	}

	if (mq->cq != NULL) {
		oce_cq_del(sc, mq->cq);
		mq->cq = NULL;
	}

	free(mq, M_DEVBUF);
	mq = NULL;
}