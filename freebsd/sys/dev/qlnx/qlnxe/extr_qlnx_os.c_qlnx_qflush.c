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
struct qlnx_fastpath {int /*<<< orphan*/  tx_mtx; int /*<<< orphan*/  tx_pkts_freed; scalar_t__ tx_br; } ;
struct mbuf {int dummy; } ;
struct ifnet {scalar_t__ if_softc; } ;
struct TYPE_3__ {int num_rss; struct qlnx_fastpath* fp_array; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT2 (TYPE_1__*,char*) ; 
 struct mbuf* drbr_dequeue (struct ifnet*,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_qflush(struct ifnet *ifp)
{
	int			rss_id;
	struct qlnx_fastpath	*fp;
	struct mbuf		*mp;
	qlnx_host_t		*ha;

	ha = (qlnx_host_t *)ifp->if_softc;

	QL_DPRINT2(ha, "enter\n");

	for (rss_id = 0; rss_id < ha->num_rss; rss_id++) {

		fp = &ha->fp_array[rss_id];

		if (fp == NULL)
			continue;

		if (fp->tx_br) {
			mtx_lock(&fp->tx_mtx);

			while ((mp = drbr_dequeue(ifp, fp->tx_br)) != NULL) { 
				fp->tx_pkts_freed++;
				m_freem(mp);			
			}
			mtx_unlock(&fp->tx_mtx);
		}
	}
	QL_DPRINT2(ha, "exit\n");

	return;
}