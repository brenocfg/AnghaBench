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
struct vm_area_struct {int vm_pgoff; int vm_end; int vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct resource {int flags; unsigned long start; int end; } ;
struct pci_controller {int isa_mem_size; scalar_t__ io_base_phys; struct resource io_resource; scalar_t__ io_base_virt; scalar_t__ isa_mem_phys; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;
typedef  int resource_size_t ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int ENXIO ; 
 int IORESOURCE_IO ; 
 int PAGE_SHIFT ; 
 int VM_SHARED ; 
 unsigned long _IO_BASE ; 
 TYPE_1__* current ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int pci_mmap_mem ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,...) ; 
 int remap_pfn_range (struct vm_area_struct*,int,int,int,int /*<<< orphan*/ ) ; 
 int shmem_zero_setup (struct vm_area_struct*) ; 

int pci_mmap_legacy_page_range(struct pci_bus *bus,
			       struct vm_area_struct *vma,
			       enum pci_mmap_state mmap_state)
{
	struct pci_controller *hose = pci_bus_to_host(bus);
	resource_size_t offset =
		((resource_size_t)vma->vm_pgoff) << PAGE_SHIFT;
	resource_size_t size = vma->vm_end - vma->vm_start;
	struct resource *rp;

	pr_debug("pci_mmap_legacy_page_range(%04x:%02x, %s @%llx..%llx)\n",
		 pci_domain_nr(bus), bus->number,
		 mmap_state == pci_mmap_mem ? "MEM" : "IO",
		 (unsigned long long)offset,
		 (unsigned long long)(offset + size - 1));

	if (mmap_state == pci_mmap_mem) {
		/* Hack alert !
		 *
		 * Because X is lame and can fail starting if it gets an error
		 * trying to mmap legacy_mem (instead of just moving on without
		 * legacy memory access) we fake it here by giving it anonymous
		 * memory, effectively behaving just like /dev/zero
		 */
		if ((offset + size) > hose->isa_mem_size) {
#ifdef CONFIG_MMU
			pr_debug("Process %s (pid:%d) mapped non-existing PCI",
				current->comm, current->pid);
			pr_debug("legacy memory for 0%04x:%02x\n",
				pci_domain_nr(bus), bus->number);
#endif
			if (vma->vm_flags & VM_SHARED)
				return shmem_zero_setup(vma);
			return 0;
		}
		offset += hose->isa_mem_phys;
	} else {
		unsigned long io_offset = (unsigned long)hose->io_base_virt -
								_IO_BASE;
		unsigned long roffset = offset + io_offset;
		rp = &hose->io_resource;
		if (!(rp->flags & IORESOURCE_IO))
			return -ENXIO;
		if (roffset < rp->start || (roffset + size) > rp->end)
			return -ENXIO;
		offset += hose->io_base_phys;
	}
	pr_debug(" -> mapping phys %llx\n", (unsigned long long)offset);

	vma->vm_pgoff = offset >> PAGE_SHIFT;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	return remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}