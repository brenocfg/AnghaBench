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
typedef  int u64 ;
typedef  int u32 ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCFSLT_SCNT ; 
 int /*<<< orphan*/  MCFSLT_SSR ; 
 int MCFSLT_SSR_TE ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int mcfslt_cnt ; 
 int mcfslt_cycles_per_jiffy ; 

__attribute__((used)) static u64 mcfslt_read_clk(struct clocksource *cs)
{
	unsigned long flags;
	u32 cycles, scnt;

	local_irq_save(flags);
	scnt = __raw_readl(TA(MCFSLT_SCNT));
	cycles = mcfslt_cnt;
	if (__raw_readl(TA(MCFSLT_SSR)) & MCFSLT_SSR_TE) {
		cycles += mcfslt_cycles_per_jiffy;
		scnt = __raw_readl(TA(MCFSLT_SCNT));
	}
	local_irq_restore(flags);

	/* subtract because slice timers count down */
	return cycles + ((mcfslt_cycles_per_jiffy - 1) - scnt);
}