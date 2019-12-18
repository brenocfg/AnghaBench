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
struct AdapterControlBlock {scalar_t__ srboutstandingcount; int /*<<< orphan*/  acb_flags; int /*<<< orphan*/  num_resets; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_BUS_RESET ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int /*<<< orphan*/  arcmsr_interrupt (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop_reset (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_bus_reset(struct AdapterControlBlock *acb)
{
	int retry = 0;

	acb->num_resets++;
	acb->acb_flags |= ACB_F_BUS_RESET;
	while(acb->srboutstandingcount != 0 && retry < 400) {
		arcmsr_interrupt(acb);
		UDELAY(25000);
		retry++;
	}
	arcmsr_iop_reset(acb);
	acb->acb_flags &= ~ACB_F_BUS_RESET;
}