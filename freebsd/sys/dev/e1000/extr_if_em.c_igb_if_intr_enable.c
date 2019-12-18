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
struct e1000_hw {int dummy; } ;
struct adapter {scalar_t__ intr_type; int que_mask; int link_mask; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EIAC ; 
 int /*<<< orphan*/  E1000_EIAM ; 
 int /*<<< orphan*/  E1000_EIMS ; 
 int /*<<< orphan*/  E1000_IMS ; 
 int E1000_IMS_LSC ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 int IMS_ENABLE_MASK ; 
 scalar_t__ __predict_true (int) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
igb_if_intr_enable(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct e1000_hw *hw = &adapter->hw;
	u32 mask;

	if (__predict_true(adapter->intr_type == IFLIB_INTR_MSIX)) {
		mask = (adapter->que_mask | adapter->link_mask);
		E1000_WRITE_REG(hw, E1000_EIAC, mask);
		E1000_WRITE_REG(hw, E1000_EIAM, mask);
		E1000_WRITE_REG(hw, E1000_EIMS, mask);
		E1000_WRITE_REG(hw, E1000_IMS, E1000_IMS_LSC);
	} else
		E1000_WRITE_REG(hw, E1000_IMS, IMS_ENABLE_MASK);
	E1000_WRITE_FLUSH(hw);
}