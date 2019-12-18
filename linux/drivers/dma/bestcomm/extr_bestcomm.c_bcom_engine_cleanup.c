#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fdt; int /*<<< orphan*/  var; int /*<<< orphan*/  ctx; int /*<<< orphan*/  tdt; TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  taskBar; int /*<<< orphan*/ * ipr; int /*<<< orphan*/ * tcr; } ;

/* Variables and functions */
 int BCOM_MAX_TASKS ; 
 TYPE_2__* bcom_eng ; 
 int /*<<< orphan*/  bcom_sram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bcom_engine_cleanup(void)
{
	int task;

	/* Stop all tasks */
	for (task=0; task<BCOM_MAX_TASKS; task++)
	{
		out_be16(&bcom_eng->regs->tcr[task], 0);
		out_8(&bcom_eng->regs->ipr[task], 0);
	}

	out_be32(&bcom_eng->regs->taskBar, 0ul);

	/* Release the SRAM zones */
	bcom_sram_free(bcom_eng->tdt);
	bcom_sram_free(bcom_eng->ctx);
	bcom_sram_free(bcom_eng->var);
	bcom_sram_free(bcom_eng->fdt);
}