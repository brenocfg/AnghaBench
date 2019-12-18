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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_INTEL_AGPCTRL ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
agp_intel_flush_tlb(device_t dev)
{
	u_int32_t val;

	val = pci_read_config(dev, AGP_INTEL_AGPCTRL, 4);
	pci_write_config(dev, AGP_INTEL_AGPCTRL, val & ~(1 << 7), 4);
	pci_write_config(dev, AGP_INTEL_AGPCTRL, val, 4);
}