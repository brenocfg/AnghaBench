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
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_DYN_CTL0 ; 
 int I40E_PFINT_DYN_CTL0_INTENA_MSK_MASK ; 
 int I40E_PFINT_DYN_CTL0_SW_ITR_INDX_MASK ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0 ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int I40E_PFINT_ICR0_ENA_ADMINQ_MASK ; 
 int I40E_PFINT_ICR0_ENA_ECC_ERR_MASK ; 
 int I40E_PFINT_ICR0_ENA_GRST_MASK ; 
 int I40E_PFINT_ICR0_ENA_HMC_ERR_MASK ; 
 int I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK ; 
 int I40E_PFINT_ICR0_ENA_PCI_EXCEPTION_MASK ; 
 int I40E_PFINT_ICR0_ENA_PE_CRITERR_MASK ; 
 int I40E_PFINT_ICR0_ENA_VFLR_MASK ; 
 int /*<<< orphan*/  I40E_PFINT_ITR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_PFINT_LNKLST0 ; 
 int /*<<< orphan*/  I40E_PFINT_STAT_CTL0 ; 
 int /*<<< orphan*/  IXL_RX_ITR ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

void
ixl_configure_intr0_msix(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 reg;

	/* First set up the adminq - vector 0 */
	wr32(hw, I40E_PFINT_ICR0_ENA, 0);  /* disable all */
	rd32(hw, I40E_PFINT_ICR0);         /* read to clear */

	reg = I40E_PFINT_ICR0_ENA_ECC_ERR_MASK |
	    I40E_PFINT_ICR0_ENA_GRST_MASK |
	    I40E_PFINT_ICR0_ENA_HMC_ERR_MASK |
	    I40E_PFINT_ICR0_ENA_ADMINQ_MASK |
	    I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK |
	    I40E_PFINT_ICR0_ENA_VFLR_MASK |
	    I40E_PFINT_ICR0_ENA_PE_CRITERR_MASK |
	    I40E_PFINT_ICR0_ENA_PCI_EXCEPTION_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, reg);

	/*
	 * 0x7FF is the end of the queue list.
	 * This means we won't use MSI-X vector 0 for a queue interrupt
	 * in MSI-X mode.
	 */
	wr32(hw, I40E_PFINT_LNKLST0, 0x7FF);
	/* Value is in 2 usec units, so 0x3E is 62*2 = 124 usecs. */
	wr32(hw, I40E_PFINT_ITR0(IXL_RX_ITR), 0x3E);

	wr32(hw, I40E_PFINT_DYN_CTL0,
	    I40E_PFINT_DYN_CTL0_SW_ITR_INDX_MASK |
	    I40E_PFINT_DYN_CTL0_INTENA_MSK_MASK);

	wr32(hw, I40E_PFINT_STAT_CTL0, 0);
}