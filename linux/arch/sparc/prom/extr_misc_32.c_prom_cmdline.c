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
struct TYPE_2__ {int /*<<< orphan*/  (* pv_abort ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AUXIO_LED ; 
 int /*<<< orphan*/  prom_lock ; 
 int /*<<< orphan*/  restore_current () ; 
 TYPE_1__* romvec ; 
 int /*<<< orphan*/  set_auxio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 

void
prom_cmdline(void)
{
	unsigned long flags;

	spin_lock_irqsave(&prom_lock, flags);
	(*(romvec->pv_abort))();
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	set_auxio(AUXIO_LED, 0);
}