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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ JZ_CGU_BASE ; 
 scalar_t__ JZ_LPCR ; 
 int LPCR_PD_SCPU ; 
 int LPCR_SCPUS ; 
 int readreg (scalar_t__) ; 
 int /*<<< orphan*/  writereg (scalar_t__,int) ; 

__attribute__((used)) static void
jz4780_core_powerup(void)
{
	uint32_t reg;

	reg = readreg(JZ_CGU_BASE + JZ_LPCR);
	reg &= ~LPCR_PD_SCPU;
	writereg(JZ_CGU_BASE + JZ_LPCR, reg);
	do {
		reg = readreg(JZ_CGU_BASE + JZ_LPCR);
	} while ((reg & LPCR_SCPUS) != 0);
}