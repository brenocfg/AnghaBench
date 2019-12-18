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
 int /*<<< orphan*/  R5K_CONF_SE ; 
 int /*<<< orphan*/  blast_r5000_scache () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  set_c0_config (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r5k_sc_enable(void)
{
	unsigned long flags;

	local_irq_save(flags);
	set_c0_config(R5K_CONF_SE);
	blast_r5000_scache();
	local_irq_restore(flags);
}