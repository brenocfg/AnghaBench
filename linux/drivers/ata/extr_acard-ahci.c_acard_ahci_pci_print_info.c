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
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct ata_host {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_CLASS_STORAGE_IDE ; 
 scalar_t__ PCI_CLASS_STORAGE_RAID ; 
 scalar_t__ PCI_CLASS_STORAGE_SATA ; 
 int /*<<< orphan*/  ahci_print_info (struct ata_host*,char const*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,scalar_t__*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acard_ahci_pci_print_info(struct ata_host *host)
{
	struct pci_dev *pdev = to_pci_dev(host->dev);
	u16 cc;
	const char *scc_s;

	pci_read_config_word(pdev, 0x0a, &cc);
	if (cc == PCI_CLASS_STORAGE_IDE)
		scc_s = "IDE";
	else if (cc == PCI_CLASS_STORAGE_SATA)
		scc_s = "SATA";
	else if (cc == PCI_CLASS_STORAGE_RAID)
		scc_s = "RAID";
	else
		scc_s = "unknown";

	ahci_print_info(host, scc_s);
}