#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ixl_pf_qtag {struct ixl_pf_qmgr* qmgr; } ;
struct ixl_pf_qmgr {TYPE_1__* qinfo; } ;
struct TYPE_2__ {int tx_configured; int rx_configured; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 size_t ixl_pf_qidx_from_vsi_qidx (struct ixl_pf_qtag*,size_t) ; 

bool
ixl_pf_qmgr_is_queue_configured(struct ixl_pf_qtag *qtag, u16 vsi_qidx, bool tx)
{
	MPASS(qtag != NULL);

	struct ixl_pf_qmgr *qmgr = qtag->qmgr;
	u16 pf_qidx = ixl_pf_qidx_from_vsi_qidx(qtag, vsi_qidx);
	if (tx)
		return (qmgr->qinfo[pf_qidx].tx_configured);
	else
		return (qmgr->qinfo[pf_qidx].rx_configured);
}