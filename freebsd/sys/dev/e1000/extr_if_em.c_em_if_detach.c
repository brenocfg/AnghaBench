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
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  e1000_phy_hw_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  em_free_pci_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_release_hw_control (struct adapter*) ; 
 int /*<<< orphan*/  em_release_manageability (struct adapter*) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
em_if_detach(if_ctx_t ctx)
{
	struct adapter	*adapter = iflib_get_softc(ctx);

	INIT_DEBUGOUT("em_if_detach: begin");

	e1000_phy_hw_reset(&adapter->hw);

	em_release_manageability(adapter);
	em_release_hw_control(adapter);
	em_free_pci_resources(ctx);

	return (0);
}