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
typedef  int u32 ;

/* Variables and functions */
 int GIC_PRIO_IRQON ; 
 int GIC_PRIO_PSR_I_SET ; 
 int PSR_I_BIT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  daif ; 
 int /*<<< orphan*/  gic_enable_sre () ; 
 int /*<<< orphan*/  gic_write_pmr (int) ; 
 int read_sysreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_gic_priority_masking(void)
{
	u32 cpuflags;

	if (WARN_ON(!gic_enable_sre()))
		return;

	cpuflags = read_sysreg(daif);

	WARN_ON(!(cpuflags & PSR_I_BIT));

	gic_write_pmr(GIC_PRIO_IRQON | GIC_PRIO_PSR_I_SET);
}