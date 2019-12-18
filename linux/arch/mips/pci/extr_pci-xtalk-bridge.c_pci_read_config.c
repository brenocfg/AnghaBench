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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int pci_conf0_read_config (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 int pci_conf1_read_config (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_is_root_bus (struct pci_bus*) ; 

__attribute__((used)) static int pci_read_config(struct pci_bus *bus, unsigned int devfn,
			   int where, int size, u32 *value)
{
	if (!pci_is_root_bus(bus))
		return pci_conf1_read_config(bus, devfn, where, size, value);

	return pci_conf0_read_config(bus, devfn, where, size, value);
}