#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irqhost; scalar_t__ coreint_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRN_EPR ; 
 int /*<<< orphan*/  ev_int_iack (int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* global_ehv_pic ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 

unsigned int ehv_pic_get_irq(void)
{
	int irq;

	BUG_ON(global_ehv_pic == NULL);

	if (global_ehv_pic->coreint_flag)
		irq = mfspr(SPRN_EPR); /* if core int mode */
	else
		ev_int_iack(0, &irq); /* legacy mode */

	if (irq == 0xFFFF)    /* 0xFFFF --> no irq is pending */
		return 0;

	/*
	 * this will also setup revmap[] in the slow path for the first
	 * time, next calls will always use fast path by indexing revmap
	 */
	return irq_linear_revmap(global_ehv_pic->irqhost, irq);
}