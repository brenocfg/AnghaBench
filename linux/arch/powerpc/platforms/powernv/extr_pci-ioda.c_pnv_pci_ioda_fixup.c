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

/* Variables and functions */
 int /*<<< orphan*/  pnv_eeh_post_init () ; 
 int /*<<< orphan*/  pnv_pci_enable_bridges () ; 
 int /*<<< orphan*/  pnv_pci_ioda_create_dbgfs () ; 
 int /*<<< orphan*/  pnv_pci_ioda_setup_PEs () ; 
 int /*<<< orphan*/  pnv_pci_ioda_setup_iommu_api () ; 

__attribute__((used)) static void pnv_pci_ioda_fixup(void)
{
	pnv_pci_ioda_setup_PEs();
	pnv_pci_ioda_setup_iommu_api();
	pnv_pci_ioda_create_dbgfs();

	pnv_pci_enable_bridges();

#ifdef CONFIG_EEH
	pnv_eeh_post_init();
#endif
}