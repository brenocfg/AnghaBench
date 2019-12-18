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
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  pci_power_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ pcie_flr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pcie_get_max_completion_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ppt_pci_reset(device_t dev)
{

	if (pcie_flr(dev,
	     max(pcie_get_max_completion_timeout(dev) / 1000, 10), true))
		return;

	pci_power_reset(dev);
}