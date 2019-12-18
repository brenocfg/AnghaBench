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
struct rsxx_cardinfo {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 unsigned char RS70_PCI_REV_SUPPORTED ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int rsxx_compatibility_check(struct rsxx_cardinfo *card)
{
	unsigned char pci_rev;

	pci_read_config_byte(card->dev, PCI_REVISION_ID, &pci_rev);

	if (pci_rev > RS70_PCI_REV_SUPPORTED)
		return -1;
	return 0;
}