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
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,unsigned int) ; 

__attribute__((used)) static void loongson_nec_fixup(struct pci_dev *pdev)
{
	unsigned int val;

	pci_read_config_dword(pdev, 0xe0, &val);
	/* Only 2 port be used */
	pci_write_config_dword(pdev, 0xe0, (val & ~3) | 0x2);
}