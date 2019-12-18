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
struct TYPE_2__ {scalar_t__ ic_error_regs; scalar_t__ ic_high_regs; } ;

/* Variables and functions */
 TYPE_1__* mv_ic_sc ; 
 int /*<<< orphan*/  mv_ic_set_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_ic_set_mask_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_ic_set_mask_hi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_mask_irq_all(void)
{

	mv_ic_set_mask(0);

	if (mv_ic_sc->ic_high_regs)
		mv_ic_set_mask_hi(0);

	if (mv_ic_sc->ic_error_regs)
		mv_ic_set_mask_error(0);
}