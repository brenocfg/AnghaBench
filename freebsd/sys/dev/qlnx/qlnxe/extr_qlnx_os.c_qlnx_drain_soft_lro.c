#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qlnx_fastpath {TYPE_1__* rxq; } ;
struct lro_entry {int dummy; } ;
struct lro_ctrl {int /*<<< orphan*/  lro_active; } ;
struct ifnet {int if_capenable; } ;
struct TYPE_5__ {int num_rss; struct qlnx_fastpath* fp_array; struct ifnet* ifp; } ;
typedef  TYPE_2__ qlnx_host_t ;
struct TYPE_4__ {struct lro_ctrl lro; } ;

/* Variables and functions */
 int IFCAP_LRO ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct lro_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  tcp_lro_flush (struct lro_ctrl*,struct lro_entry*) ; 
 int /*<<< orphan*/  tcp_lro_flush_all (struct lro_ctrl*) ; 

__attribute__((used)) static void
qlnx_drain_soft_lro(qlnx_host_t *ha)
{
#ifdef QLNX_SOFT_LRO

	struct ifnet	*ifp;
	int		i;

	ifp = ha->ifp;


	if (ifp->if_capenable & IFCAP_LRO) {

	        for (i = 0; i < ha->num_rss; i++) {

			struct qlnx_fastpath *fp = &ha->fp_array[i];
			struct lro_ctrl *lro;

			lro = &fp->rxq->lro;

#if (__FreeBSD_version >= 1100101) || (defined QLNX_QSORT_LRO)

			tcp_lro_flush_all(lro);

#else
			struct lro_entry *queued;

			while ((!SLIST_EMPTY(&lro->lro_active))){
				queued = SLIST_FIRST(&lro->lro_active);
				SLIST_REMOVE_HEAD(&lro->lro_active, next);
				tcp_lro_flush(lro, queued);
			}

#endif /* #if (__FreeBSD_version >= 1100101) || (defined QLNX_QSORT_LRO) */

                }
	}

#endif /* #ifdef QLNX_SOFT_LRO */

	return;
}