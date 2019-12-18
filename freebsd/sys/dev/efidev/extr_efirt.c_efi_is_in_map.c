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
typedef  uintptr_t vm_offset_t ;
struct efi_md {int md_attr; uintptr_t md_pages; scalar_t__ md_virt; } ;

/* Variables and functions */
 int EFI_MD_ATTR_RT ; 
 uintptr_t PAGE_SIZE ; 
 struct efi_md* efi_next_descriptor (struct efi_md*,int) ; 

__attribute__((used)) static bool
efi_is_in_map(struct efi_md *map, int ndesc, int descsz, vm_offset_t addr)
{
	struct efi_md *p;
	int i;

	for (i = 0, p = map; i < ndesc; i++, p = efi_next_descriptor(p,
	    descsz)) {
		if ((p->md_attr & EFI_MD_ATTR_RT) == 0)
			continue;

		if (addr >= (uintptr_t)p->md_virt &&
		    addr < (uintptr_t)p->md_virt + p->md_pages * PAGE_SIZE)
			return (true);
	}

	return (false);
}