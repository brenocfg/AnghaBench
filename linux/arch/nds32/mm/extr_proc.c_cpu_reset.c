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
 int CACHE_CTL_mskDC_EN ; 
 int CACHE_CTL_mskIC_EN ; 
 int /*<<< orphan*/  GIE_DISABLE () ; 
 int /*<<< orphan*/  NDS32_SR_CACHE_CTL ; 
 int __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr_isb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_dcache_wbinval_all () ; 
 int /*<<< orphan*/  cpu_icache_inval_all () ; 

void cpu_reset(unsigned long reset)
{
	u32 tmp;
	GIE_DISABLE();
	tmp = __nds32__mfsr(NDS32_SR_CACHE_CTL);
	tmp &= ~(CACHE_CTL_mskIC_EN | CACHE_CTL_mskDC_EN);
	__nds32__mtsr_isb(tmp, NDS32_SR_CACHE_CTL);
	cpu_dcache_wbinval_all();
	cpu_icache_inval_all();

	__asm__ __volatile__("jr.toff %0\n\t"::"r"(reset));
}