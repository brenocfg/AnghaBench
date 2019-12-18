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
struct TYPE_2__ {int /*<<< orphan*/  conf; int /*<<< orphan*/  options; int /*<<< orphan*/  options_dyn; } ;
struct cpuinfo_mips {TYPE_1__ guest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 unsigned int MIPS_CONF5_LLB ; 
 unsigned int MIPS_CONF5_MRP ; 
 unsigned int MIPS_CONF5_MVH ; 
 unsigned int MIPS_CONF_M ; 
 int /*<<< orphan*/  MIPS_CPU_MAAR ; 
 int /*<<< orphan*/  MIPS_CPU_MVH ; 
 int /*<<< orphan*/  MIPS_CPU_RW_LLB ; 
 int /*<<< orphan*/  probe_gc0_config_dyn (unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int decode_guest_config5(struct cpuinfo_mips *c)
{
	unsigned int config5, config5_dyn;

	probe_gc0_config_dyn(config5, config5, config5_dyn,
			 MIPS_CONF_M | MIPS_CONF5_MVH | MIPS_CONF5_MRP);

	if (config5 & MIPS_CONF5_MRP)
		c->guest.options |= MIPS_CPU_MAAR;
	if (config5_dyn & MIPS_CONF5_MRP)
		c->guest.options_dyn |= MIPS_CPU_MAAR;

	if (config5 & MIPS_CONF5_LLB)
		c->guest.options |= MIPS_CPU_RW_LLB;

	if (config5 & MIPS_CONF5_MVH)
		c->guest.options |= MIPS_CPU_MVH;

	if (config5 & MIPS_CONF_M)
		c->guest.conf |= BIT(6);
	return config5 & MIPS_CONF_M;
}