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
typedef  int u64 ;
struct kern_memdesc {int attribute; } ;

/* Variables and functions */
 int EFI_MEMORY_WB ; 
 int efi_mem_attribute (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kern_memmap ; 
 struct kern_memdesc* kern_memory_descriptor (unsigned long) ; 
 unsigned long kmd_end (struct kern_memdesc*) ; 

u64
kern_mem_attribute (unsigned long phys_addr, unsigned long size)
{
	unsigned long end = phys_addr + size;
	struct kern_memdesc *md;
	u64 attr;

	/*
	 * This is a hack for ioremap calls before we set up kern_memmap.
	 * Maybe we should do efi_memmap_init() earlier instead.
	 */
	if (!kern_memmap) {
		attr = efi_mem_attribute(phys_addr, size);
		if (attr & EFI_MEMORY_WB)
			return EFI_MEMORY_WB;
		return 0;
	}

	md = kern_memory_descriptor(phys_addr);
	if (!md)
		return 0;

	attr = md->attribute;
	do {
		unsigned long md_end = kmd_end(md);

		if (end <= md_end)
			return attr;

		md = kern_memory_descriptor(md_end);
		if (!md || md->attribute != attr)
			return 0;
	} while (md);
	return 0;	/* never reached */
}