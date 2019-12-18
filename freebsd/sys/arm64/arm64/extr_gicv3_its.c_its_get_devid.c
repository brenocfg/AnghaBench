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
typedef  uintptr_t uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ID_MSI ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pci_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 

__attribute__((used)) static uint32_t
its_get_devid(device_t pci_dev)
{
	uintptr_t id;

	if (pci_get_id(pci_dev, PCI_ID_MSI, &id) != 0)
		panic("its_get_devid: Unable to get the MSI DeviceID");

	return (id);
}