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
struct lro_ctrl {int dummy; } ;
struct TYPE_6__ {scalar_t__ lro_init; } ;
struct TYPE_7__ {int num_rx_rings; TYPE_2__ flags; TYPE_1__* rx_ring; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_5__ {struct lro_ctrl lro; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_lro_free (struct lro_ctrl*) ; 

__attribute__((used)) static void
qls_free_lro(qla_host_t *ha)
{
        int i;
        struct lro_ctrl *lro;

        if (!ha->flags.lro_init)
                return;

        for (i = 0; i < ha->num_rx_rings; i++) {
                lro = &ha->rx_ring[i].lro;
                tcp_lro_free(lro);
        }
        ha->flags.lro_init = 0;
}