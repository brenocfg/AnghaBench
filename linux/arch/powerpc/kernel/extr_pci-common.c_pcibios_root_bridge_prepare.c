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
struct pci_host_bridge {int dummy; } ;
struct TYPE_2__ {int (* pcibios_root_bridge_prepare ) (struct pci_host_bridge*) ;} ;

/* Variables and functions */
 TYPE_1__ ppc_md ; 
 int stub1 (struct pci_host_bridge*) ; 

int pcibios_root_bridge_prepare(struct pci_host_bridge *bridge)
{
	if (ppc_md.pcibios_root_bridge_prepare)
		return ppc_md.pcibios_root_bridge_prepare(bridge);

	return 0;
}