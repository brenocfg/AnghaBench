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
struct platform_device {int dummy; } ;
struct oxnas_pcie {int /*<<< orphan*/  phy; } ;
struct TYPE_2__ {int refcount; } ;

/* Variables and functions */
 TYPE_1__ pcie_shared ; 
 int /*<<< orphan*/  phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oxnas_pcie_shared_init(struct platform_device *pdev, struct oxnas_pcie *pcie)
{
	if (++pcie_shared.refcount == 1) {
		phy_init(pcie->phy);
		phy_power_on(pcie->phy);
		return 0;
	} else {
		return 0;
	}
}