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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_IOBASEH_1 ; 
 int /*<<< orphan*/  PCIR_IOBASEL_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITL_1 ; 
 int /*<<< orphan*/  PCIR_MEMBASE_1 ; 
 int /*<<< orphan*/  PCIR_MEMLIMIT_1 ; 
 int /*<<< orphan*/  PCIR_PMBASEH_1 ; 
 int /*<<< orphan*/  PCIR_PMBASEL_1 ; 
 int /*<<< orphan*/  PCIR_PMLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_PMLIMITL_1 ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
pcib_bridge_init(device_t dev)
{
	pci_write_config(dev, PCIR_IOBASEL_1, 0xff, 1);
	pci_write_config(dev, PCIR_IOBASEH_1, 0xffff, 2);
	pci_write_config(dev, PCIR_IOLIMITL_1, 0, 1);
	pci_write_config(dev, PCIR_IOLIMITH_1, 0, 2);
	pci_write_config(dev, PCIR_MEMBASE_1, 0xffff, 2);
	pci_write_config(dev, PCIR_MEMLIMIT_1, 0, 2);
	pci_write_config(dev, PCIR_PMBASEL_1, 0xffff, 2);
	pci_write_config(dev, PCIR_PMBASEH_1, 0xffffffff, 4);
	pci_write_config(dev, PCIR_PMLIMITL_1, 0, 2);
	pci_write_config(dev, PCIR_PMLIMITH_1, 0, 4);
}