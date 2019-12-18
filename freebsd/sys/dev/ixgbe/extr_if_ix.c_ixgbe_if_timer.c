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
typedef  scalar_t__ uint16_t ;
struct adapter {int /*<<< orphan*/  link_up; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  hw; scalar_t__ sfp_probe; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_check_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_sfp_probe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgbe_if_timer(if_ctx_t ctx, uint16_t qid)
{
	struct adapter *adapter = iflib_get_softc(ctx);

	if (qid != 0)
		return;

	/* Check for pluggable optics */
	if (adapter->sfp_probe)
		if (!ixgbe_sfp_probe(ctx))
			return; /* Nothing to do */

	ixgbe_check_link(&adapter->hw, &adapter->link_speed,
	    &adapter->link_up, 0);

	/* Fire off the adminq task */
	iflib_admin_intr_deferred(ctx);

}