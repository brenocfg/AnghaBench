#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pfil_head {int dummy; } ;
typedef  TYPE_1__* iflib_rxq_t ;
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_6__ {TYPE_1__* ifc_rxqs; } ;
struct TYPE_5__ {struct pfil_head* pfil; } ;

/* Variables and functions */
 int NRXQSETS (TYPE_2__*) ; 
 int /*<<< orphan*/  pfil_head_unregister (struct pfil_head*) ; 

__attribute__((used)) static void
iflib_rem_pfil(if_ctx_t ctx)
{
	struct pfil_head *pfil;
	iflib_rxq_t rxq;
	int i;

	rxq = ctx->ifc_rxqs;
	pfil = rxq->pfil;
	for (i = 0; i < NRXQSETS(ctx); i++, rxq++) {
		rxq->pfil = NULL;
	}
	pfil_head_unregister(pfil);
}