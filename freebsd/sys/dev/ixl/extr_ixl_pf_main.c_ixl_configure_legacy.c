#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ixl_vsi {int tx_itr_setting; int rx_itr_setting; TYPE_2__* rx_queues; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int tx_itr; int rx_itr; struct ixl_vsi vsi; struct i40e_hw hw; } ;
struct TYPE_8__ {int itr; } ;
struct TYPE_7__ {int itr; } ;
struct TYPE_5__ {int itr; } ;
struct TYPE_6__ {TYPE_1__ rxr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int I40E_PFINT_ICR0_ENA_ADMINQ_MASK ; 
 int I40E_PFINT_ICR0_ENA_ECC_ERR_MASK ; 
 int I40E_PFINT_ICR0_ENA_GRST_MASK ; 
 int I40E_PFINT_ICR0_ENA_HMC_ERR_MASK ; 
 int I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK ; 
 int I40E_PFINT_ICR0_ENA_PCI_EXCEPTION_MASK ; 
 int I40E_PFINT_ICR0_ENA_PE_CRITERR_MASK ; 
 int I40E_PFINT_ICR0_ENA_VFLR_MASK ; 
 int /*<<< orphan*/  I40E_PFINT_ITR0 (int) ; 
 int /*<<< orphan*/  I40E_PFINT_LNKLST0 ; 
 int /*<<< orphan*/  I40E_PFINT_STAT_CTL0 ; 
 int I40E_PFINT_STAT_CTL0_OTHER_ITR_INDX_SHIFT ; 
 int /*<<< orphan*/  I40E_QINT_RQCTL (int /*<<< orphan*/ ) ; 
 int I40E_QINT_RQCTL_CAUSE_ENA_MASK ; 
 int I40E_QINT_RQCTL_ITR_INDX_SHIFT ; 
 int I40E_QINT_RQCTL_NEXTQ_TYPE_SHIFT ; 
 int /*<<< orphan*/  I40E_QINT_TQCTL (int /*<<< orphan*/ ) ; 
 int I40E_QINT_TQCTL_CAUSE_ENA_MASK ; 
 int I40E_QINT_TQCTL_ITR_INDX_SHIFT ; 
 int I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT ; 
 int I40E_QUEUE_TYPE_TX ; 
 int IXL_ITR_NONE ; 
 int IXL_QUEUE_EOL ; 
 int IXL_RX_ITR ; 
 int IXL_TX_ITR ; 
 TYPE_4__* rxr ; 
 TYPE_3__* txr ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

void
ixl_configure_legacy(struct ixl_pf *pf)
{
	struct i40e_hw	*hw = &pf->hw;
	struct ixl_vsi	*vsi = &pf->vsi;
	u32 reg;

// TODO: Fix
#if 0
	/* Configure ITR */
	vsi->tx_itr_setting = pf->tx_itr;
	wr32(hw, I40E_PFINT_ITR0(IXL_TX_ITR),
	    vsi->tx_itr_setting);
	txr->itr = vsi->tx_itr_setting;

	vsi->rx_itr_setting = pf->rx_itr;
	wr32(hw, I40E_PFINT_ITR0(IXL_RX_ITR),
	    vsi->rx_itr_setting);
	rxr->itr = vsi->rx_itr_setting;
	/* XXX: Assuming only 1 queue in single interrupt mode */
#endif
	vsi->rx_queues[0].rxr.itr = vsi->rx_itr_setting;

	/* Setup "other" causes */
	reg = I40E_PFINT_ICR0_ENA_ECC_ERR_MASK
	    | I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK
	    | I40E_PFINT_ICR0_ENA_GRST_MASK
	    | I40E_PFINT_ICR0_ENA_PCI_EXCEPTION_MASK
	    | I40E_PFINT_ICR0_ENA_HMC_ERR_MASK
	    | I40E_PFINT_ICR0_ENA_PE_CRITERR_MASK
	    | I40E_PFINT_ICR0_ENA_VFLR_MASK
	    | I40E_PFINT_ICR0_ENA_ADMINQ_MASK
	    ;
	wr32(hw, I40E_PFINT_ICR0_ENA, reg);

	/* No ITR for non-queue interrupts */
	wr32(hw, I40E_PFINT_STAT_CTL0,
	    IXL_ITR_NONE << I40E_PFINT_STAT_CTL0_OTHER_ITR_INDX_SHIFT);

	/* FIRSTQ_INDX = 0, FIRSTQ_TYPE = 0 (rx) */
	wr32(hw, I40E_PFINT_LNKLST0, 0);

	/* Associate the queue pair to the vector and enable the q int */
	reg = I40E_QINT_RQCTL_CAUSE_ENA_MASK
	    | (IXL_RX_ITR << I40E_QINT_RQCTL_ITR_INDX_SHIFT)
	    | (I40E_QUEUE_TYPE_TX << I40E_QINT_RQCTL_NEXTQ_TYPE_SHIFT);
	wr32(hw, I40E_QINT_RQCTL(0), reg);

	reg = I40E_QINT_TQCTL_CAUSE_ENA_MASK
	    | (IXL_TX_ITR << I40E_QINT_TQCTL_ITR_INDX_SHIFT)
	    | (IXL_QUEUE_EOL << I40E_QINT_TQCTL_NEXTQ_INDX_SHIFT);
	wr32(hw, I40E_QINT_TQCTL(0), reg);
}