#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int get_link_status; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct adapter {int /*<<< orphan*/  mta; int /*<<< orphan*/  has_amt; scalar_t__ has_manage; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  em_add_hw_stats (struct adapter*) ; 
 int /*<<< orphan*/  em_free_pci_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_get_hw_control (struct adapter*) ; 
 int /*<<< orphan*/  em_if_queues_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_if_update_admin_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_release_hw_control (struct adapter*) ; 
 int /*<<< orphan*/  em_reset (int /*<<< orphan*/ ) ; 
 int em_setup_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_update_stats_counters (struct adapter*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
em_if_attach_post(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct e1000_hw *hw = &adapter->hw;
	int error = 0;
	
	/* Setup OS specific network interface */
	error = em_setup_interface(ctx);
	if (error != 0) {
		goto err_late;
	}

	em_reset(ctx);

	/* Initialize statistics */
	em_update_stats_counters(adapter);
	hw->mac.get_link_status = 1;
	em_if_update_admin_status(ctx);
	em_add_hw_stats(adapter);

	/* Non-AMT based hardware can now take control from firmware */
	if (adapter->has_manage && !adapter->has_amt)
		em_get_hw_control(adapter);

	INIT_DEBUGOUT("em_if_attach_post: end");

	return (error);

err_late:
	em_release_hw_control(adapter);
	em_free_pci_resources(ctx);
	em_if_queues_free(ctx);
	free(adapter->mta, M_DEVBUF);

	return (error);
}