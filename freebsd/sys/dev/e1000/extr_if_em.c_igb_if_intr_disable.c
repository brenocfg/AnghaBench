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
struct e1000_hw {int dummy; } ;
struct adapter {scalar_t__ intr_type; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EIAC ; 
 int /*<<< orphan*/  E1000_EIMC ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 scalar_t__ __predict_true (int) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
igb_if_intr_disable(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct e1000_hw *hw = &adapter->hw;

	if (__predict_true(adapter->intr_type == IFLIB_INTR_MSIX)) {
		E1000_WRITE_REG(hw, E1000_EIMC, 0xffffffff);
		E1000_WRITE_REG(hw, E1000_EIAC, 0);
	}
	E1000_WRITE_REG(hw, E1000_IMC, 0xffffffff);
	E1000_WRITE_FLUSH(hw);
}