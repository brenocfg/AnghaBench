#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_drv_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  fp_task; int /*<<< orphan*/ * fp_taskqueue; } ;
typedef  TYPE_2__ qla_tx_fp_t ;
struct TYPE_8__ {int sds_idx; TYPE_5__* ha; } ;
typedef  TYPE_3__ qla_ivec_t ;
struct TYPE_9__ {int num_sds_rings; TYPE_1__* sds; } ;
typedef  TYPE_4__ qla_hw_t ;
struct TYPE_10__ {TYPE_2__* tx_fp; TYPE_4__ hw; struct ifnet* ifp; } ;
typedef  TYPE_5__ qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  intr_count; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ql_isr(void *arg)
{
	qla_ivec_t *ivec = arg;
	qla_host_t *ha ;
	int idx;
	qla_hw_t *hw;
	struct ifnet *ifp;
	qla_tx_fp_t *fp;

	ha = ivec->ha;
	hw = &ha->hw;
	ifp = ha->ifp;

	if ((idx = ivec->sds_idx) >= ha->hw.num_sds_rings)
		return;

	fp = &ha->tx_fp[idx];
	hw->sds[idx].intr_count++;

	if ((fp->fp_taskqueue != NULL) &&
		(ifp->if_drv_flags & IFF_DRV_RUNNING))
		taskqueue_enqueue(fp->fp_taskqueue, &fp->fp_task);

	return;
}