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
 int ENXIO ; 
 int xlp_pcie_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xlp_alloc_msi(device_t pcib, device_t dev, int count, int maxcount, int *irqs)
{
	int i, link;

	/*
	 * Each link has 32 MSIs that can be allocated, but for now
	 * we only support one device per link.
	 * msi_alloc() equivalent is needed when we start supporting
	 * bridges on the PCIe link.
	 */
	link = xlp_pcie_link(pcib, dev);
	if (link == -1)
		return (ENXIO);

	/*
	 * encode the irq so that we know it is a MSI interrupt when we
	 * setup interrupts
	 */
	for (i = 0; i < count; i++)
		irqs[i] = 64 + link * 32 + i;

	return (0);
}