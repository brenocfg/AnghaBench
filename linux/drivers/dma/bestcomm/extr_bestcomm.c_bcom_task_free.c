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
struct bcom_task {size_t tasknum; struct bcom_task* cookie; int /*<<< orphan*/  bd; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {TYPE_1__* tdt; } ;
struct TYPE_3__ {scalar_t__ stop; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcom_disable_task (size_t) ; 
 TYPE_2__* bcom_eng ; 
 int /*<<< orphan*/  bcom_sram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bcom_task*) ; 

void
bcom_task_free(struct bcom_task *tsk)
{
	/* Stop the task */
	bcom_disable_task(tsk->tasknum);

	/* Clear TDT */
	bcom_eng->tdt[tsk->tasknum].start = 0;
	bcom_eng->tdt[tsk->tasknum].stop  = 0;

	/* Free everything */
	irq_dispose_mapping(tsk->irq);
	bcom_sram_free(tsk->bd);
	kfree(tsk->cookie);
	kfree(tsk);
}