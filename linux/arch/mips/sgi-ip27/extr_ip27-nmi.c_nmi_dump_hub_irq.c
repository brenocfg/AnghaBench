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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PI_INT_MASK0_A ; 
 int /*<<< orphan*/  PI_INT_MASK0_B ; 
 int /*<<< orphan*/  PI_INT_MASK1_A ; 
 int /*<<< orphan*/  PI_INT_MASK1_B ; 
 int /*<<< orphan*/  PI_INT_PEND0 ; 
 int /*<<< orphan*/  PI_INT_PEND1 ; 
 int /*<<< orphan*/  REMOTE_HUB_L (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 

void nmi_dump_hub_irq(nasid_t nasid, int slice)
{
	u64 mask0, mask1, pend0, pend1;

	if (slice == 0) {				/* Slice A */
		mask0 = REMOTE_HUB_L(nasid, PI_INT_MASK0_A);
		mask1 = REMOTE_HUB_L(nasid, PI_INT_MASK1_A);
	} else {					/* Slice B */
		mask0 = REMOTE_HUB_L(nasid, PI_INT_MASK0_B);
		mask1 = REMOTE_HUB_L(nasid, PI_INT_MASK1_B);
	}

	pend0 = REMOTE_HUB_L(nasid, PI_INT_PEND0);
	pend1 = REMOTE_HUB_L(nasid, PI_INT_PEND1);

	pr_emerg("PI_INT_MASK0: %16llx PI_INT_MASK1: %16llx\n", mask0, mask1);
	pr_emerg("PI_INT_PEND0: %16llx PI_INT_PEND1: %16llx\n", pend0, pend1);
	pr_emerg("\n\n");
}