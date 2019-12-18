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
typedef  int u64 ;
struct TYPE_2__ {int tb_armed; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_BCM1480_SCD_PERF_CNT_CFG0 ; 
 int /*<<< orphan*/  A_BCM1480_SCD_PERF_CNT_CFG1 ; 
 int /*<<< orphan*/  A_SCD_PERF_CNT_1 ; 
 int /*<<< orphan*/  A_SCD_PERF_CNT_CFG ; 
 int /*<<< orphan*/  A_SCD_TRACE_CFG ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int M_SCD_TRACE_CFG_FORCECNT ; 
 int M_SCD_TRACE_CFG_FREEZE_FULL ; 
 int M_SCD_TRACE_CFG_RESET ; 
 int M_SPC_CFG_CLEAR ; 
 int M_SPC_CFG_ENABLE ; 
 int M_SPC_CFG_SRC1 ; 
 int V_SPC_CFG_SRC1 (int) ; 
 int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ sbp ; 
 int tb_period ; 

__attribute__((used)) static void arm_tb(void)
{
	u64 scdperfcnt;
	u64 next = (1ULL << 40) - tb_period;
	u64 tb_options = M_SCD_TRACE_CFG_FREEZE_FULL;

	/*
	 * Generate an SCD_PERFCNT interrupt in TB_PERIOD Zclks to
	 * trigger start of trace.  XXX vary sampling period
	 */
	__raw_writeq(0, IOADDR(A_SCD_PERF_CNT_1));
	scdperfcnt = __raw_readq(IOADDR(A_SCD_PERF_CNT_CFG));

	/*
	 * Unfortunately, in Pass 2 we must clear all counters to knock down
	 * a previous interrupt request.  This means that bus profiling
	 * requires ALL of the SCD perf counters.
	 */
#if defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	__raw_writeq((scdperfcnt & ~M_SPC_CFG_SRC1) |
						/* keep counters 0,2,3,4,5,6,7 as is */
		     V_SPC_CFG_SRC1(1),		/* counter 1 counts cycles */
		     IOADDR(A_BCM1480_SCD_PERF_CNT_CFG0));
	__raw_writeq(
		     M_SPC_CFG_ENABLE |		/* enable counting */
		     M_SPC_CFG_CLEAR |		/* clear all counters */
		     V_SPC_CFG_SRC1(1),		/* counter 1 counts cycles */
		     IOADDR(A_BCM1480_SCD_PERF_CNT_CFG1));
#else
	__raw_writeq((scdperfcnt & ~M_SPC_CFG_SRC1) |
						/* keep counters 0,2,3 as is */
		     M_SPC_CFG_ENABLE |		/* enable counting */
		     M_SPC_CFG_CLEAR |		/* clear all counters */
		     V_SPC_CFG_SRC1(1),		/* counter 1 counts cycles */
		     IOADDR(A_SCD_PERF_CNT_CFG));
#endif
	__raw_writeq(next, IOADDR(A_SCD_PERF_CNT_1));
	/* Reset the trace buffer */
	__raw_writeq(M_SCD_TRACE_CFG_RESET, IOADDR(A_SCD_TRACE_CFG));
#if 0 && defined(M_SCD_TRACE_CFG_FORCECNT)
	/* XXXKW may want to expose control to the data-collector */
	tb_options |= M_SCD_TRACE_CFG_FORCECNT;
#endif
	__raw_writeq(tb_options, IOADDR(A_SCD_TRACE_CFG));
	sbp.tb_armed = 1;
}