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
typedef  unsigned long u64 ;
struct vm_area_struct {unsigned long vm_pgoff; unsigned long vm_end; unsigned long vm_start; int vm_flags; void* vm_page_prot; } ;
struct qlnxr_ucontext {int dpi; int dpi_size; } ;
struct qlnxr_dev {unsigned long db_phys_addr; unsigned long db_size; int /*<<< orphan*/ * ha; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int VM_READ ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_ucontext* get_qlnxr_ucontext (struct ib_ucontext*) ; 
 int io_remap_pfn_range (struct vm_area_struct*,int,unsigned long,unsigned long,void*) ; 
 void* pgprot_writecombine (void*) ; 
 int qlnxr_search_mmap (struct qlnxr_ucontext*,unsigned long,unsigned long) ; 

int
qlnxr_mmap(struct ib_ucontext *context, struct vm_area_struct *vma)
{
	struct qlnxr_ucontext	*ucontext = get_qlnxr_ucontext(context);
	struct qlnxr_dev	*dev = get_qlnxr_dev((context->device));
	unsigned long		vm_page = vma->vm_pgoff << PAGE_SHIFT;
	u64 			unmapped_db;
	unsigned long 		len = (vma->vm_end - vma->vm_start);
	int 			rc = 0;
	bool 			found;
	qlnx_host_t		*ha;

	ha = dev->ha;

#if __FreeBSD_version > 1102000
	unmapped_db = dev->db_phys_addr + (ucontext->dpi * ucontext->dpi_size);
#else
	unmapped_db = dev->db_phys_addr;
#endif /* #if __FreeBSD_version > 1102000 */

	QL_DPRINT12(ha, "qedr_mmap enter vm_page=0x%lx"
		" vm_pgoff=0x%lx unmapped_db=0x%llx db_size=%x, len=%lx\n",
		vm_page, vma->vm_pgoff, unmapped_db,
		dev->db_size, len);

	if ((vma->vm_start & (PAGE_SIZE - 1)) || (len & (PAGE_SIZE - 1))) {
		QL_DPRINT11(ha, "Vma_start not page aligned "
			"vm_start = %ld vma_end = %ld\n", vma->vm_start,
			vma->vm_end);
		return -EINVAL;
	}

	found = qlnxr_search_mmap(ucontext, vm_page, len);
	if (!found) {
		QL_DPRINT11(ha, "Vma_pgoff not found in mapped array = %ld\n",
			vma->vm_pgoff);
		return -EINVAL;
	}

	QL_DPRINT12(ha, "Mapping doorbell bar\n");

#if __FreeBSD_version > 1102000

	if ((vm_page < unmapped_db) ||
		((vm_page + len) > (unmapped_db + ucontext->dpi_size))) {
		QL_DPRINT11(ha, "failed pages are outside of dpi;"
			"page address=0x%lx, unmapped_db=0x%lx, dpi_size=0x%x\n",
			vm_page, unmapped_db, ucontext->dpi_size);
		return -EINVAL;
	}

	if (vma->vm_flags & VM_READ) {
		QL_DPRINT11(ha, "failed mmap, cannot map doorbell bar for read\n");
		return -EINVAL;
	}

	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	rc = io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, len,
			vma->vm_page_prot);

#else

	if ((vm_page >= unmapped_db) && (vm_page <= (unmapped_db +
		dev->db_size))) {

		QL_DPRINT12(ha, "Mapping doorbell bar\n");

		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

		rc = io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
					    PAGE_SIZE, vma->vm_page_prot);
	} else {
		QL_DPRINT12(ha, "Mapping chains\n");
		rc = io_remap_pfn_range(vma, vma->vm_start,
					 vma->vm_pgoff, len, vma->vm_page_prot);
	}

#endif /* #if __FreeBSD_version > 1102000 */

	QL_DPRINT12(ha, "exit [%d]\n", rc);
	return rc;
}