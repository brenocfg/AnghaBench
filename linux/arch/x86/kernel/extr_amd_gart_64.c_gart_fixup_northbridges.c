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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_GARTAPERTUREBASE ; 
 int /*<<< orphan*/  AMD_NB_GART ; 
 int /*<<< orphan*/  amd_nb_has_feature (int /*<<< orphan*/ ) ; 
 int amd_nb_num () ; 
 int aperture_alloc ; 
 int /*<<< orphan*/  aperture_order ; 
 int /*<<< orphan*/  fix_up_north_bridges ; 
 int /*<<< orphan*/  gart_set_size_and_enable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 TYPE_1__* node_to_amd_nb (int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void gart_fixup_northbridges(void)
{
	int i;

	if (!fix_up_north_bridges)
		return;

	if (!amd_nb_has_feature(AMD_NB_GART))
		return;

	pr_info("PCI-DMA: Restoring GART aperture settings\n");

	for (i = 0; i < amd_nb_num(); i++) {
		struct pci_dev *dev = node_to_amd_nb(i)->misc;

		/*
		 * Don't enable translations just yet.  That is the next
		 * step.  Restore the pre-suspend aperture settings.
		 */
		gart_set_size_and_enable(dev, aperture_order);
		pci_write_config_dword(dev, AMD64_GARTAPERTUREBASE, aperture_alloc >> 25);
	}
}