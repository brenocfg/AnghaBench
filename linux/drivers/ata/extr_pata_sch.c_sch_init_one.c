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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ata_port_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_VERSION ; 
 int ata_pci_bmdma_init_one (struct pci_dev*,struct ata_port_info const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_print_version_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ata_port_info const sch_port_info ; 
 int /*<<< orphan*/  sch_sht ; 

__attribute__((used)) static int sch_init_one(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	const struct ata_port_info *ppi[] = { &sch_port_info, NULL };

	ata_print_version_once(&pdev->dev, DRV_VERSION);

	return ata_pci_bmdma_init_one(pdev, ppi, &sch_sht, NULL, 0);
}