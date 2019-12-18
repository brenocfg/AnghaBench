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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_3 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_5 ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdev ; 

__attribute__((used)) static void
touch_bars(device_t dev)
{
	/*
	 * Don't enable yet
	 */
#if !defined(__LP64__) && 0
	u32 v;

	pci_read_config_dword(pdev, PCI_BASE_ADDRESS_1, &v);
	pci_write_config_dword(pdev, PCI_BASE_ADDRESS_1, v);
	pci_read_config_dword(pdev, PCI_BASE_ADDRESS_3, &v);
	pci_write_config_dword(pdev, PCI_BASE_ADDRESS_3, v);
	pci_read_config_dword(pdev, PCI_BASE_ADDRESS_5, &v);
	pci_write_config_dword(pdev, PCI_BASE_ADDRESS_5, v);
#endif
}