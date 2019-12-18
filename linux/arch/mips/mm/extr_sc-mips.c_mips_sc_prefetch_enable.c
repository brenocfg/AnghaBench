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

/* Variables and functions */
 int CM_GCR_L2_PFT_CONTROL_B_CEN ; 
 int CM_GCR_L2_PFT_CONTROL_B_PORTID ; 
 unsigned long CM_GCR_L2_PFT_CONTROL_NPFT ; 
 unsigned long CM_GCR_L2_PFT_CONTROL_PAGEMASK ; 
 unsigned long CM_GCR_L2_PFT_CONTROL_PFTEN ; 
 scalar_t__ CM_REV_CM2_5 ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ mips_cm_revision () ; 
 unsigned long read_gcr_l2_pft_control () ; 
 int /*<<< orphan*/  set_gcr_l2_pft_control_b (int) ; 
 int /*<<< orphan*/  write_gcr_l2_pft_control (unsigned long) ; 

__attribute__((used)) static void mips_sc_prefetch_enable(void)
{
	unsigned long pftctl;

	if (mips_cm_revision() < CM_REV_CM2_5)
		return;

	/*
	 * If there is one or more L2 prefetch unit present then enable
	 * prefetching for both code & data, for all ports.
	 */
	pftctl = read_gcr_l2_pft_control();
	if (pftctl & CM_GCR_L2_PFT_CONTROL_NPFT) {
		pftctl &= ~CM_GCR_L2_PFT_CONTROL_PAGEMASK;
		pftctl |= PAGE_MASK & CM_GCR_L2_PFT_CONTROL_PAGEMASK;
		pftctl |= CM_GCR_L2_PFT_CONTROL_PFTEN;
		write_gcr_l2_pft_control(pftctl);

		set_gcr_l2_pft_control_b(CM_GCR_L2_PFT_CONTROL_B_PORTID |
					 CM_GCR_L2_PFT_CONTROL_B_CEN);
	}
}