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
struct adapter {int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VTEIAC ; 
 int /*<<< orphan*/  IXGBE_VTEIMC ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixv_if_disable_intr(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_VTEIAC, 0);
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_VTEIMC, ~0);
	IXGBE_WRITE_FLUSH(&adapter->hw);
}