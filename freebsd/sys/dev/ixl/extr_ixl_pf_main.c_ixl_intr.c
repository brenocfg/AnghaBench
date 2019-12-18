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
struct ixl_vsi {int /*<<< orphan*/  ctx; struct ixl_rx_queue* rx_queues; } ;
struct ixl_rx_queue {int /*<<< orphan*/  irqs; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {scalar_t__ msix; struct ixl_vsi vsi; struct i40e_hw hw; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 int /*<<< orphan*/  I40E_PFINT_DYN_CTL0 ; 
 int I40E_PFINT_DYN_CTLN_CLEARPBA_MASK ; 
 int I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0 ; 
 int I40E_PFINT_ICR0_ADMINQ_MASK ; 
 int I40E_PFINT_ICR0_QUEUE_0_MASK ; 
 int I40E_PFINT_ICR0_VFLR_MASK ; 
 int IXL_ITR_NONE ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_iov_intr_deferred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_enable_intr0 (struct i40e_hw*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

int
ixl_intr(void *arg)
{
	struct ixl_pf		*pf = arg;
	struct i40e_hw		*hw =  &pf->hw;
	struct ixl_vsi		*vsi = &pf->vsi;
	struct ixl_rx_queue	*que = vsi->rx_queues;
        u32			icr0;

	// pf->admin_irq++
	++que->irqs;

// TODO: Check against proper field
#if 0
	/* Clear PBA at start of ISR if using legacy interrupts */
	if (pf->msix == 0)
		wr32(hw, I40E_PFINT_DYN_CTL0,
		    I40E_PFINT_DYN_CTLN_CLEARPBA_MASK |
		    (IXL_ITR_NONE << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT));
#endif

	icr0 = rd32(hw, I40E_PFINT_ICR0);


#ifdef PCI_IOV
	if (icr0 & I40E_PFINT_ICR0_VFLR_MASK)
		iflib_iov_intr_deferred(vsi->ctx);
#endif

	// TODO!: Do the stuff that's done in ixl_msix_adminq here, too!
	if (icr0 & I40E_PFINT_ICR0_ADMINQ_MASK)
		iflib_admin_intr_deferred(vsi->ctx);
 
	// TODO: Is intr0 enabled somewhere else?
	ixl_enable_intr0(hw);

	if (icr0 & I40E_PFINT_ICR0_QUEUE_0_MASK)
		return (FILTER_SCHEDULE_THREAD);
	else
		return (FILTER_HANDLED);
}