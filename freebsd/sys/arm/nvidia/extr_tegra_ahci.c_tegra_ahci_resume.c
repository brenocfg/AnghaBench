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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ahci_ctlr_setup (int /*<<< orphan*/ ) ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 int tegra_ahci_ctlr_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_ahci_resume(device_t dev)
{
	int res;

	if ((res = tegra_ahci_ctlr_reset(dev)) != 0)
		return (res);
	ahci_ctlr_setup(dev);
	return (bus_generic_resume(dev));
}