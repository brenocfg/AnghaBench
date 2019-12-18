#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int C_SW0 ; 
 int /*<<< orphan*/  EVPE_ENABLE ; 
 int /*<<< orphan*/  dvpe () ; 
 int /*<<< orphan*/  evpe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int read_vpe_c0_cause () ; 
 int /*<<< orphan*/  settc (int) ; 
 int /*<<< orphan*/  write_vpe_c0_cause (int) ; 

void _interrupt_sp(void)
{
	unsigned long flags;

	local_irq_save(flags);
	dvpe();
	settc(1);
	write_vpe_c0_cause(read_vpe_c0_cause() | C_SW0);
	evpe(EVPE_ENABLE);
	local_irq_restore(flags);
}