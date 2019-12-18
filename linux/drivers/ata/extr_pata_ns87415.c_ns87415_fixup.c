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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void ns87415_fixup(struct pci_dev *pdev)
{
	/* Select 512 byte sectors */
	pci_write_config_byte(pdev, 0x55, 0xEE);
	/* Select PIO0 8bit clocking */
	pci_write_config_byte(pdev, 0x54, 0xB7);
}