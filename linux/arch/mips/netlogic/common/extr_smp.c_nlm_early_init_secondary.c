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
struct TYPE_2__ {int /*<<< orphan*/  ebase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_CM_CMASK ; 
 int /*<<< orphan*/  change_c0_config (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* nlm_current_node () ; 
 int /*<<< orphan*/  write_c0_ebase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_mmu_init () ; 

void nlm_early_init_secondary(int cpu)
{
	change_c0_config(CONF_CM_CMASK, 0x3);
#ifdef CONFIG_CPU_XLP
	xlp_mmu_init();
#endif
	write_c0_ebase(nlm_current_node()->ebase);
}