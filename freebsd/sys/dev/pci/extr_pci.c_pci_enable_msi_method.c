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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct pcicfg_msi {int msi_ctrl; scalar_t__ msi_location; } ;
struct TYPE_2__ {struct pcicfg_msi msi; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_MSICTRL_64BIT ; 
 int PCIM_MSICTRL_MSI_ENABLE ; 
 scalar_t__ PCIR_MSI_ADDR ; 
 scalar_t__ PCIR_MSI_ADDR_HIGH ; 
 scalar_t__ PCIR_MSI_CTRL ; 
 scalar_t__ PCIR_MSI_DATA ; 
 scalar_t__ PCIR_MSI_DATA_64BIT ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ht_map_msi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

void
pci_enable_msi_method(device_t dev, device_t child, uint64_t address,
    uint16_t data)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	struct pcicfg_msi *msi = &dinfo->cfg.msi;

	/* Write data and address values. */
	pci_write_config(child, msi->msi_location + PCIR_MSI_ADDR,
	    address & 0xffffffff, 4);
	if (msi->msi_ctrl & PCIM_MSICTRL_64BIT) {
		pci_write_config(child, msi->msi_location + PCIR_MSI_ADDR_HIGH,
		    address >> 32, 4);
		pci_write_config(child, msi->msi_location + PCIR_MSI_DATA_64BIT,
		    data, 2);
	} else
		pci_write_config(child, msi->msi_location + PCIR_MSI_DATA, data,
		    2);

	/* Enable MSI in the control register. */
	msi->msi_ctrl |= PCIM_MSICTRL_MSI_ENABLE;
	pci_write_config(child, msi->msi_location + PCIR_MSI_CTRL,
	    msi->msi_ctrl, 2);

	/* Enable MSI -> HT mapping. */
	pci_ht_map_msi(child, address);
}