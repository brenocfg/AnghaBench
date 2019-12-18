#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lro_entry {int dummy; } ;
struct lro_ctrl {int /*<<< orphan*/  lro_active; } ;
struct TYPE_6__ {int num_sds_rings; TYPE_1__* sds; } ;
typedef  TYPE_2__ qla_hw_t ;
struct TYPE_7__ {TYPE_2__ hw; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_5__ {struct lro_ctrl lro; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct lro_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  tcp_lro_flush (struct lro_ctrl*,struct lro_entry*) ; 
 int /*<<< orphan*/  tcp_lro_flush_all (struct lro_ctrl*) ; 

__attribute__((used)) static void
qla_drain_soft_lro(qla_host_t *ha)
{
        int i;
        qla_hw_t *hw = &ha->hw;
        struct lro_ctrl *lro;

       	for (i = 0; i < hw->num_sds_rings; i++) {
               	lro = &hw->sds[i].lro;

#if (__FreeBSD_version >= 1100101)
		tcp_lro_flush_all(lro);
#else
                struct lro_entry *queued;

		while ((!SLIST_EMPTY(&lro->lro_active))) {
			queued = SLIST_FIRST(&lro->lro_active);
			SLIST_REMOVE_HEAD(&lro->lro_active, next);
			tcp_lro_flush(lro, queued);
		}
#endif /* #if (__FreeBSD_version >= 1100101) */
	}

	return;
}