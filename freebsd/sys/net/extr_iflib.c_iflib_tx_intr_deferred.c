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
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_5__ {TYPE_1__* ifc_txqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ift_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPTASK_ENQUEUE (int /*<<< orphan*/ *) ; 

void
iflib_tx_intr_deferred(if_ctx_t ctx, int txqid)
{

	GROUPTASK_ENQUEUE(&ctx->ifc_txqs[txqid].ift_task);
}