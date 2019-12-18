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
typedef  int /*<<< orphan*/  u32 ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  state; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA ; 
 int /*<<< orphan*/  I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK ; 
 int /*<<< orphan*/  IXL_PF_STATE_MDD_PENDING ; 
 int /*<<< orphan*/  atomic_clear_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_handle_rx_mdd_event (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_handle_tx_mdd_event (struct ixl_pf*) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ixl_handle_mdd_event(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 reg;

	/*
	 * Handle both TX/RX because it's possible they could
	 * both trigger in the same interrupt.
	 */
	ixl_handle_tx_mdd_event(pf);
	ixl_handle_rx_mdd_event(pf);

	atomic_clear_32(&pf->state, IXL_PF_STATE_MDD_PENDING);

	/* re-enable mdd interrupt cause */
	reg = rd32(hw, I40E_PFINT_ICR0_ENA);
	reg |= I40E_PFINT_ICR0_ENA_MAL_DETECT_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, reg);
	ixl_flush(hw);
}