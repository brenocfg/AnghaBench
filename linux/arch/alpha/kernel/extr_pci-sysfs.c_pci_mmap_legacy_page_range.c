#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct pci_controller {int dummy; } ;
struct pci_bus {TYPE_2__* legacy_io; TYPE_1__* legacy_mem; struct pci_controller* sysdata; } ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;
struct TYPE_4__ {unsigned long size; } ;
struct TYPE_3__ {unsigned long size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __legacy_mmap_fits (struct pci_controller*,struct vm_area_struct*,unsigned long,int) ; 
 int has_sparse (struct pci_controller*,int) ; 
 int hose_mmap_page_range (struct pci_controller*,struct vm_area_struct*,int,int) ; 
 int pci_mmap_mem ; 

int pci_mmap_legacy_page_range(struct pci_bus *bus, struct vm_area_struct *vma,
			       enum pci_mmap_state mmap_type)
{
	struct pci_controller *hose = bus->sysdata;
	int sparse = has_sparse(hose, mmap_type);
	unsigned long res_size;

	res_size = (mmap_type == pci_mmap_mem) ? bus->legacy_mem->size :
						 bus->legacy_io->size;
	if (!__legacy_mmap_fits(hose, vma, res_size, sparse))
		return -EINVAL;

	return hose_mmap_page_range(hose, vma, mmap_type, sparse);
}