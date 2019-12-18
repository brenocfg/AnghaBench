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
typedef  int /*<<< orphan*/  xen_pfn_t ;
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_mm; } ;
struct remap_data {int contiguous; int no_translate; struct mmu_update* mmu_update; int /*<<< orphan*/  prot; int /*<<< orphan*/ * pfn; } ;
struct page {int dummy; } ;
struct mmu_update {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HYPERVISOR_mmu_update (struct mmu_update*,int,int*,unsigned int) ; 
 unsigned long PAGE_SHIFT ; 
 int REMAP_BATCH_SIZE ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int apply_to_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,struct remap_data*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int min (int,int) ; 
 int /*<<< orphan*/  remap_area_pfn_pte_fn ; 
 int /*<<< orphan*/  xen_flush_tlb_all () ; 

int xen_remap_pfn(struct vm_area_struct *vma, unsigned long addr,
		  xen_pfn_t *pfn, int nr, int *err_ptr, pgprot_t prot,
		  unsigned int domid, bool no_translate, struct page **pages)
{
	int err = 0;
	struct remap_data rmd;
	struct mmu_update mmu_update[REMAP_BATCH_SIZE];
	unsigned long range;
	int mapped = 0;

	BUG_ON(!((vma->vm_flags & (VM_PFNMAP | VM_IO)) == (VM_PFNMAP | VM_IO)));

	rmd.pfn = pfn;
	rmd.prot = prot;
	/*
	 * We use the err_ptr to indicate if there we are doing a contiguous
	 * mapping or a discontigious mapping.
	 */
	rmd.contiguous = !err_ptr;
	rmd.no_translate = no_translate;

	while (nr) {
		int index = 0;
		int done = 0;
		int batch = min(REMAP_BATCH_SIZE, nr);
		int batch_left = batch;

		range = (unsigned long)batch << PAGE_SHIFT;

		rmd.mmu_update = mmu_update;
		err = apply_to_page_range(vma->vm_mm, addr, range,
					  remap_area_pfn_pte_fn, &rmd);
		if (err)
			goto out;

		/*
		 * We record the error for each page that gives an error, but
		 * continue mapping until the whole set is done
		 */
		do {
			int i;

			err = HYPERVISOR_mmu_update(&mmu_update[index],
						    batch_left, &done, domid);

			/*
			 * @err_ptr may be the same buffer as @gfn, so
			 * only clear it after each chunk of @gfn is
			 * used.
			 */
			if (err_ptr) {
				for (i = index; i < index + done; i++)
					err_ptr[i] = 0;
			}
			if (err < 0) {
				if (!err_ptr)
					goto out;
				err_ptr[i] = err;
				done++; /* Skip failed frame. */
			} else
				mapped += done;
			batch_left -= done;
			index += done;
		} while (batch_left);

		nr -= batch;
		addr += range;
		if (err_ptr)
			err_ptr += batch;
		cond_resched();
	}
out:

	xen_flush_tlb_all();

	return err < 0 ? err : mapped;
}