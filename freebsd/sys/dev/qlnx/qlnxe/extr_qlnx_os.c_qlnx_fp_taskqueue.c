#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlnx_fastpath {int /*<<< orphan*/  tx_mtx; scalar_t__ tx_pkts_completed; int /*<<< orphan*/  tx_pkts_compl_fp; scalar_t__ tx_pkts_transmitted; int /*<<< orphan*/  tx_pkts_trans_fp; int /*<<< orphan*/  tx_br; scalar_t__ edev; } ;
struct ifnet {int if_drv_flags; } ;
struct TYPE_3__ {struct ifnet* ifp; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  QL_DPRINT2 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  drbr_empty (struct ifnet*,int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_transmit_locked (struct ifnet*,struct qlnx_fastpath*,int /*<<< orphan*/ *) ; 
 scalar_t__ tx_compl ; 
 scalar_t__ tx_pkts ; 

__attribute__((used)) static void
qlnx_fp_taskqueue(void *context, int pending)
{
        struct qlnx_fastpath	*fp;
        qlnx_host_t		*ha;
        struct ifnet		*ifp;

        fp = context;

        if (fp == NULL)
                return;

	ha = (qlnx_host_t *)fp->edev;

	ifp = ha->ifp;

        if(ifp->if_drv_flags & IFF_DRV_RUNNING) {

                if (!drbr_empty(ifp, fp->tx_br)) {

                        if(mtx_trylock(&fp->tx_mtx)) {

#ifdef QLNX_TRACE_PERF_DATA
                                tx_pkts = fp->tx_pkts_transmitted;
                                tx_compl = fp->tx_pkts_completed;
#endif

                                qlnx_transmit_locked(ifp, fp, NULL);

#ifdef QLNX_TRACE_PERF_DATA
                                fp->tx_pkts_trans_fp +=
					(fp->tx_pkts_transmitted - tx_pkts);
                                fp->tx_pkts_compl_fp +=
					(fp->tx_pkts_completed - tx_compl);
#endif
                                mtx_unlock(&fp->tx_mtx);
                        }
                }
        }

        QL_DPRINT2(ha, "exit \n");
        return;
}