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
struct pci_controller {int /*<<< orphan*/  io_resource; int /*<<< orphan*/  pci_io_size; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static resource_size_t pcibios_io_size(const struct pci_controller *hose)
{
#ifdef CONFIG_PPC64
	return hose->pci_io_size;
#else
	return resource_size(&hose->io_resource);
#endif
}