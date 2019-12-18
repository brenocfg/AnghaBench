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
struct xgbe_phy_if {int /*<<< orphan*/  phy_config_aneg; int /*<<< orphan*/  phy_status; int /*<<< orphan*/  phy_stop; int /*<<< orphan*/  phy_start; int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  phy_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_phy_config_aneg ; 
 int /*<<< orphan*/  xgbe_phy_init ; 
 int /*<<< orphan*/  xgbe_phy_reset ; 
 int /*<<< orphan*/  xgbe_phy_start ; 
 int /*<<< orphan*/  xgbe_phy_status ; 
 int /*<<< orphan*/  xgbe_phy_stop ; 

void xgbe_init_function_ptrs_phy(struct xgbe_phy_if *phy_if)
{
	phy_if->phy_init        = xgbe_phy_init;

	phy_if->phy_reset       = xgbe_phy_reset;
	phy_if->phy_start       = xgbe_phy_start;
	phy_if->phy_stop        = xgbe_phy_stop;

	phy_if->phy_status      = xgbe_phy_status;
	phy_if->phy_config_aneg = xgbe_phy_config_aneg;
}