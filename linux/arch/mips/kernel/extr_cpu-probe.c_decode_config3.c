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
struct cpuinfo_mips {int options; scalar_t__ htw_seq; int /*<<< orphan*/  ases; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_ASE_DSP ; 
 int /*<<< orphan*/  MIPS_ASE_DSP2P ; 
 int /*<<< orphan*/  MIPS_ASE_DSP3 ; 
 int /*<<< orphan*/  MIPS_ASE_MIPSMT ; 
 int /*<<< orphan*/  MIPS_ASE_MSA ; 
 int /*<<< orphan*/  MIPS_ASE_SMARTMIPS ; 
 int /*<<< orphan*/  MIPS_ASE_VZ ; 
 unsigned int MIPS_CONF3_BI ; 
 unsigned int MIPS_CONF3_BP ; 
 unsigned int MIPS_CONF3_CDMM ; 
 unsigned int MIPS_CONF3_CTXTC ; 
 unsigned int MIPS_CONF3_DSP ; 
 unsigned int MIPS_CONF3_DSP2P ; 
 unsigned int MIPS_CONF3_ISA ; 
 unsigned int MIPS_CONF3_LPA ; 
 unsigned int MIPS_CONF3_MSA ; 
 unsigned int MIPS_CONF3_MT ; 
 unsigned int MIPS_CONF3_PW ; 
 unsigned int MIPS_CONF3_RXI ; 
 unsigned int MIPS_CONF3_SC ; 
 unsigned int MIPS_CONF3_SM ; 
 unsigned int MIPS_CONF3_SP ; 
 unsigned int MIPS_CONF3_ULRI ; 
 unsigned int MIPS_CONF3_VEIC ; 
 unsigned int MIPS_CONF3_VINT ; 
 unsigned int MIPS_CONF3_VZ ; 
 unsigned int MIPS_CONF_M ; 
 int MIPS_CPU_BADINSTR ; 
 int MIPS_CPU_BADINSTRP ; 
 int MIPS_CPU_CDMM ; 
 int MIPS_CPU_CTXTC ; 
 int MIPS_CPU_HTW ; 
 int MIPS_CPU_LPA ; 
 int MIPS_CPU_MICROMIPS ; 
 int MIPS_CPU_RIXI ; 
 int MIPS_CPU_SEGMENTS ; 
 int MIPS_CPU_SP ; 
 int MIPS_CPU_ULRI ; 
 int MIPS_CPU_VEIC ; 
 int MIPS_CPU_VINT ; 
 scalar_t__ cpu_has_mips_r6 ; 
 unsigned int read_c0_config3 () ; 

__attribute__((used)) static inline unsigned int decode_config3(struct cpuinfo_mips *c)
{
	unsigned int config3;

	config3 = read_c0_config3();

	if (config3 & MIPS_CONF3_SM) {
		c->ases |= MIPS_ASE_SMARTMIPS;
		c->options |= MIPS_CPU_RIXI | MIPS_CPU_CTXTC;
	}
	if (config3 & MIPS_CONF3_RXI)
		c->options |= MIPS_CPU_RIXI;
	if (config3 & MIPS_CONF3_CTXTC)
		c->options |= MIPS_CPU_CTXTC;
	if (config3 & MIPS_CONF3_DSP)
		c->ases |= MIPS_ASE_DSP;
	if (config3 & MIPS_CONF3_DSP2P) {
		c->ases |= MIPS_ASE_DSP2P;
		if (cpu_has_mips_r6)
			c->ases |= MIPS_ASE_DSP3;
	}
	if (config3 & MIPS_CONF3_VINT)
		c->options |= MIPS_CPU_VINT;
	if (config3 & MIPS_CONF3_VEIC)
		c->options |= MIPS_CPU_VEIC;
	if (config3 & MIPS_CONF3_LPA)
		c->options |= MIPS_CPU_LPA;
	if (config3 & MIPS_CONF3_MT)
		c->ases |= MIPS_ASE_MIPSMT;
	if (config3 & MIPS_CONF3_ULRI)
		c->options |= MIPS_CPU_ULRI;
	if (config3 & MIPS_CONF3_ISA)
		c->options |= MIPS_CPU_MICROMIPS;
	if (config3 & MIPS_CONF3_VZ)
		c->ases |= MIPS_ASE_VZ;
	if (config3 & MIPS_CONF3_SC)
		c->options |= MIPS_CPU_SEGMENTS;
	if (config3 & MIPS_CONF3_BI)
		c->options |= MIPS_CPU_BADINSTR;
	if (config3 & MIPS_CONF3_BP)
		c->options |= MIPS_CPU_BADINSTRP;
	if (config3 & MIPS_CONF3_MSA)
		c->ases |= MIPS_ASE_MSA;
	if (config3 & MIPS_CONF3_PW) {
		c->htw_seq = 0;
		c->options |= MIPS_CPU_HTW;
	}
	if (config3 & MIPS_CONF3_CDMM)
		c->options |= MIPS_CPU_CDMM;
	if (config3 & MIPS_CONF3_SP)
		c->options |= MIPS_CPU_SP;

	return config3 & MIPS_CONF_M;
}