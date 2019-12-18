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
struct TYPE_2__ {int /*<<< orphan*/  (* pv_reboot ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__* romvec ; 
 int /*<<< orphan*/  stub1 (char*) ; 

void
prom_reboot(char *bcommand)
{
	unsigned long flags;
	local_irq_save(flags);
	(*(romvec->pv_reboot))(bcommand);
	local_irq_restore(flags);
}