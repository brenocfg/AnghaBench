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
 int /*<<< orphan*/  generic_pcie_get_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intr_alloc_msix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
generic_pcie_acpi_alloc_msix(device_t pci, device_t child, int *irq)
{

#if defined(INTRNG)
	return (intr_alloc_msix(pci, child, generic_pcie_get_xref(pci, child),
	    irq));
#else
	return (ENXIO);
#endif
}