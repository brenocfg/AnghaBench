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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct efi_md {int md_attr; int md_phys; int md_pages; int /*<<< orphan*/ * md_virt; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pml4_entry_t ;

/* Variables and functions */
 int EFI_MD_ATTR_RT ; 
 int EFI_MD_ATTR_UC ; 
 int EFI_MD_ATTR_WB ; 
 int EFI_MD_ATTR_WC ; 
 int EFI_MD_ATTR_WP ; 
 int EFI_MD_ATTR_WT ; 
 int EFI_PAGE_MASK ; 
 int EFI_PAGE_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int NPDEPG ; 
 int NPDPEPG ; 
 int NPML4EPG ; 
 int /*<<< orphan*/  OBJT_PHYS ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int VM_MAXUSER_ADDRESS ; 
 int VM_MEMATTR_UNCACHEABLE ; 
 int VM_MEMATTR_WRITE_BACK ; 
 int VM_MEMATTR_WRITE_COMBINING ; 
 int VM_MEMATTR_WRITE_PROTECTED ; 
 int VM_MEMATTR_WRITE_THROUGH ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 scalar_t__ bootverbose ; 
 scalar_t__ efi_1t1_idx ; 
 int /*<<< orphan*/  efi_1t1_page () ; 
 int /*<<< orphan*/ * efi_1t1_pte (int) ; 
 int /*<<< orphan*/  efi_destroy_1t1_map () ; 
 struct efi_md* efi_next_descriptor (struct efi_md*,int) ; 
 int /*<<< orphan*/ * efi_pml4 ; 
 int /*<<< orphan*/  efi_pml4_page ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  obj_1t1_pt ; 
 int pmap_cache_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pinit_pml4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  pte_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptoa (int) ; 
 int /*<<< orphan*/  vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
efi_create_1t1_map(struct efi_md *map, int ndesc, int descsz)
{
	struct efi_md *p;
	pt_entry_t *pte;
	vm_offset_t va;
	uint64_t idx;
	int bits, i, mode;

	obj_1t1_pt = vm_pager_allocate(OBJT_PHYS, NULL, ptoa(1 +
	    NPML4EPG + NPML4EPG * NPDPEPG + NPML4EPG * NPDPEPG * NPDEPG),
	    VM_PROT_ALL, 0, NULL);
	efi_1t1_idx = 0;
	VM_OBJECT_WLOCK(obj_1t1_pt);
	efi_pml4_page = efi_1t1_page();
	VM_OBJECT_WUNLOCK(obj_1t1_pt);
	efi_pml4 = (pml4_entry_t *)PHYS_TO_DMAP(VM_PAGE_TO_PHYS(efi_pml4_page));
	pmap_pinit_pml4(efi_pml4_page);

	for (i = 0, p = map; i < ndesc; i++, p = efi_next_descriptor(p,
	    descsz)) {
		if ((p->md_attr & EFI_MD_ATTR_RT) == 0)
			continue;
		if (p->md_virt != NULL && (uint64_t)p->md_virt != p->md_phys) {
			if (bootverbose)
				printf("EFI Runtime entry %d is mapped\n", i);
			goto fail;
		}
		if ((p->md_phys & EFI_PAGE_MASK) != 0) {
			if (bootverbose)
				printf("EFI Runtime entry %d is not aligned\n",
				    i);
			goto fail;
		}
		if (p->md_phys + p->md_pages * EFI_PAGE_SIZE < p->md_phys ||
		    p->md_phys + p->md_pages * EFI_PAGE_SIZE >=
		    VM_MAXUSER_ADDRESS) {
			printf("EFI Runtime entry %d is not in mappable for RT:"
			    "base %#016jx %#jx pages\n",
			    i, (uintmax_t)p->md_phys,
			    (uintmax_t)p->md_pages);
			goto fail;
		}
		if ((p->md_attr & EFI_MD_ATTR_WB) != 0)
			mode = VM_MEMATTR_WRITE_BACK;
		else if ((p->md_attr & EFI_MD_ATTR_WT) != 0)
			mode = VM_MEMATTR_WRITE_THROUGH;
		else if ((p->md_attr & EFI_MD_ATTR_WC) != 0)
			mode = VM_MEMATTR_WRITE_COMBINING;
		else if ((p->md_attr & EFI_MD_ATTR_WP) != 0)
			mode = VM_MEMATTR_WRITE_PROTECTED;
		else if ((p->md_attr & EFI_MD_ATTR_UC) != 0)
			mode = VM_MEMATTR_UNCACHEABLE;
		else {
			if (bootverbose)
				printf("EFI Runtime entry %d mapping "
				    "attributes unsupported\n", i);
			mode = VM_MEMATTR_UNCACHEABLE;
		}
		bits = pmap_cache_bits(kernel_pmap, mode, FALSE) | X86_PG_RW |
		    X86_PG_V;
		VM_OBJECT_WLOCK(obj_1t1_pt);
		for (va = p->md_phys, idx = 0; idx < p->md_pages; idx++,
		    va += PAGE_SIZE) {
			pte = efi_1t1_pte(va);
			pte_store(pte, va | bits);
		}
		VM_OBJECT_WUNLOCK(obj_1t1_pt);
	}

	return (true);

fail:
	efi_destroy_1t1_map();
	return (false);
}