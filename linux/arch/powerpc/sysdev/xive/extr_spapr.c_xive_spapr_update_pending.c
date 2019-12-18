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
typedef  int u8 ;
typedef  int u16 ;
struct xive_cpu {int pending_prio; int cppr; } ;

/* Variables and functions */
 int TM_QW1_NSR_EO ; 
 scalar_t__ TM_SPC_ACK_OS_REG ; 
 int /*<<< orphan*/  __raw_readw (scalar_t__) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ xive_tima ; 

__attribute__((used)) static void xive_spapr_update_pending(struct xive_cpu *xc)
{
	u8 nsr, cppr;
	u16 ack;

	/*
	 * Perform the "Acknowledge O/S to Register" cycle.
	 *
	 * Let's speedup the access to the TIMA using the raw I/O
	 * accessor as we don't need the synchronisation routine of
	 * the higher level ones
	 */
	ack = be16_to_cpu(__raw_readw(xive_tima + TM_SPC_ACK_OS_REG));

	/* Synchronize subsequent queue accesses */
	mb();

	/*
	 * Grab the CPPR and the "NSR" field which indicates the source
	 * of the interrupt (if any)
	 */
	cppr = ack & 0xff;
	nsr = ack >> 8;

	if (nsr & TM_QW1_NSR_EO) {
		if (cppr == 0xff)
			return;
		/* Mark the priority pending */
		xc->pending_prio |= 1 << cppr;

		/*
		 * A new interrupt should never have a CPPR less favored
		 * than our current one.
		 */
		if (cppr >= xc->cppr)
			pr_err("CPU %d odd ack CPPR, got %d at %d\n",
			       smp_processor_id(), cppr, xc->cppr);

		/* Update our idea of what the CPPR is */
		xc->cppr = cppr;
	}
}