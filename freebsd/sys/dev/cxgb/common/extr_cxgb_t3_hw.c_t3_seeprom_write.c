#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {unsigned int vpd_cap_addr; } ;
struct TYPE_10__ {TYPE_1__ pci; } ;
struct TYPE_11__ {TYPE_2__ params; } ;
typedef  TYPE_3__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ERR (TYPE_3__*,char*,int) ; 
 int EEPROMSIZE ; 
 int EEPROM_MAX_POLL ; 
 int EEPROM_STAT_ADDR ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ PCI_VPD_ADDR ; 
 int PCI_VPD_ADDR_F ; 
 scalar_t__ PCI_VPD_DATA ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  t3_os_pci_read_config_2 (TYPE_3__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  t3_os_pci_write_config_2 (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  t3_os_pci_write_config_4 (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 

int t3_seeprom_write(adapter_t *adapter, u32 addr, u32 data)
{
	u16 val;
	int attempts = EEPROM_MAX_POLL;
	unsigned int base = adapter->params.pci.vpd_cap_addr;

	if ((addr >= EEPROMSIZE && addr != EEPROM_STAT_ADDR) || (addr & 3))
		return -EINVAL;

	t3_os_pci_write_config_4(adapter, base + PCI_VPD_DATA,
				 cpu_to_le32(data));
	t3_os_pci_write_config_2(adapter, base + PCI_VPD_ADDR,
				 (u16)addr | PCI_VPD_ADDR_F);
	do {
		msleep(1);
		t3_os_pci_read_config_2(adapter, base + PCI_VPD_ADDR, &val);
	} while ((val & PCI_VPD_ADDR_F) && --attempts);

	if (val & PCI_VPD_ADDR_F) {
		CH_ERR(adapter, "write to EEPROM address 0x%x failed\n", addr);
		return -EIO;
	}
	return 0;
}