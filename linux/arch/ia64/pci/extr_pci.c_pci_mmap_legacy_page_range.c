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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct pci_bus {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  enum pci_mmap_state { ____Placeholder_pci_mmap_state } pci_mmap_state ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOSYS ; 
 scalar_t__ IS_ERR (char*) ; 
 unsigned long PAGE_SHIFT ; 
 int PTR_ERR (char*) ; 
 char* pci_get_legacy_mem (struct pci_bus*) ; 
 int pci_mmap_mem ; 
 int /*<<< orphan*/  phys_mem_access_prot (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_mmap_phys_addr_range (unsigned long,unsigned long) ; 

int
pci_mmap_legacy_page_range(struct pci_bus *bus, struct vm_area_struct *vma,
			   enum pci_mmap_state mmap_state)
{
	unsigned long size = vma->vm_end - vma->vm_start;
	pgprot_t prot;
	char *addr;

	/* We only support mmap'ing of legacy memory space */
	if (mmap_state != pci_mmap_mem)
		return -ENOSYS;

	/*
	 * Avoid attribute aliasing.  See Documentation/ia64/aliasing.rst
	 * for more details.
	 */
	if (!valid_mmap_phys_addr_range(vma->vm_pgoff, size))
		return -EINVAL;
	prot = phys_mem_access_prot(NULL, vma->vm_pgoff, size,
				    vma->vm_page_prot);

	addr = pci_get_legacy_mem(bus);
	if (IS_ERR(addr))
		return PTR_ERR(addr);

	vma->vm_pgoff += (unsigned long)addr >> PAGE_SHIFT;
	vma->vm_page_prot = prot;

	if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			    size, vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}