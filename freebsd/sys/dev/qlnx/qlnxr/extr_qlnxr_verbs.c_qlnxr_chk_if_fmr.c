#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t cons; } ;
struct qlnxr_qp {TYPE_3__ sq; TYPE_5__* wqe_wr_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  completed; } ;
struct TYPE_12__ {TYPE_4__ info; } ;
struct TYPE_11__ {scalar_t__ opcode; TYPE_2__* frmr; TYPE_6__* mr; } ;
struct TYPE_7__ {int /*<<< orphan*/  completed; } ;
struct TYPE_8__ {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ IB_WC_FAST_REG_MR ; 
 scalar_t__ IB_WC_REG_MR ; 

__attribute__((used)) static inline void
qlnxr_chk_if_fmr(struct qlnxr_qp *qp)
{
#if __FreeBSD_version >= 1102000

	if (qp->wqe_wr_id[qp->sq.cons].opcode == IB_WC_REG_MR)
		qp->wqe_wr_id[qp->sq.cons].mr->info.completed++;
#else
	if (qp->wqe_wr_id[qp->sq.cons].opcode == IB_WC_FAST_REG_MR)
		qp->wqe_wr_id[qp->sq.cons].frmr->info.completed++;

#endif /* #if __FreeBSD_version >= 1102000 */
}