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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ HT_MSI_ADDR_HI ; 
 scalar_t__ HT_MSI_ADDR_LO ; 
 int HT_MSI_ADDR_LO_MASK ; 
 int HT_MSI_FIXED_ADDR ; 
 scalar_t__ HT_MSI_FLAGS ; 
 int HT_MSI_FLAGS_FIXED ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static u64 read_ht_magic_addr(struct pci_dev *pdev, unsigned int pos)
{
	u8 flags;
	u32 tmp;
	u64 addr;

	pci_read_config_byte(pdev, pos + HT_MSI_FLAGS, &flags);

	if (flags & HT_MSI_FLAGS_FIXED)
		return HT_MSI_FIXED_ADDR;

	pci_read_config_dword(pdev, pos + HT_MSI_ADDR_LO, &tmp);
	addr = tmp & HT_MSI_ADDR_LO_MASK;
	pci_read_config_dword(pdev, pos + HT_MSI_ADDR_HI, &tmp);
	addr = addr | ((u64)tmp << 32);

	return addr;
}