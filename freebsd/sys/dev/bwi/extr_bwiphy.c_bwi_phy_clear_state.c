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
struct bwi_phy {int /*<<< orphan*/  phy_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_CLEAR_PHY_FLAGS ; 

void
bwi_phy_clear_state(struct bwi_phy *phy)
{
	phy->phy_flags &= ~BWI_CLEAR_PHY_FLAGS;
}