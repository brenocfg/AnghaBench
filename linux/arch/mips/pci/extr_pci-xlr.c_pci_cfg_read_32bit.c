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
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_cfg_addr (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ pci_config_base ; 

__attribute__((used)) static inline u32 pci_cfg_read_32bit(struct pci_bus *bus, unsigned int devfn,
	int where)
{
	u32 data;
	u32 *cfgaddr;

	cfgaddr = (u32 *)(pci_config_base +
			pci_cfg_addr(bus->number, devfn, where & ~3));
	data = *cfgaddr;
	return cpu_to_le32(data);
}