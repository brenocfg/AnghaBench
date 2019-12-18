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
typedef  scalar_t__ u16 ;
struct ixl_pf_qtag {scalar_t__ num_allocated; struct ixl_pf_qmgr* qmgr; } ;
struct ixl_pf_qmgr {TYPE_1__* qinfo; } ;
struct TYPE_2__ {scalar_t__ tx_enabled; scalar_t__ rx_enabled; scalar_t__ rx_configured; scalar_t__ tx_configured; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 scalar_t__ ixl_pf_qidx_from_vsi_qidx (struct ixl_pf_qtag*,scalar_t__) ; 

void
ixl_pf_qmgr_clear_queue_flags(struct ixl_pf_qtag *qtag)
{
	MPASS(qtag != NULL);

	struct ixl_pf_qmgr *qmgr = qtag->qmgr;
	for (u16 i = 0; i < qtag->num_allocated; i++) {
		u16 pf_qidx = ixl_pf_qidx_from_vsi_qidx(qtag, i);

		qmgr->qinfo[pf_qidx].tx_configured = 0;
		qmgr->qinfo[pf_qidx].rx_configured = 0;
		qmgr->qinfo[pf_qidx].rx_enabled = 0;
		qmgr->qinfo[pf_qidx].tx_enabled = 0;
	}
}