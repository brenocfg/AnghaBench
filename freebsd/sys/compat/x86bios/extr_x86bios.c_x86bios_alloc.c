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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  X86BIOS_PAGE_SIZE ; 
 int /*<<< orphan*/  X86BIOS_RAM_BASE ; 
 void* contigmalloc (size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtophys (void*) ; 
 int /*<<< orphan*/  x86bios_lock ; 
 int /*<<< orphan*/  x86bios_rom_phys ; 
 int /*<<< orphan*/  x86bios_set_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void *
x86bios_alloc(uint32_t *offset, size_t size, int flags)
{
	void *vaddr;

	if (offset == NULL || size == 0)
		return (NULL);
	vaddr = contigmalloc(size, M_DEVBUF, flags, X86BIOS_RAM_BASE,
	    x86bios_rom_phys, X86BIOS_PAGE_SIZE, 0);
	if (vaddr != NULL) {
		*offset = vtophys(vaddr);
		mtx_lock(&x86bios_lock);
		x86bios_set_pages((vm_offset_t)vaddr, *offset, size);
		mtx_unlock(&x86bios_lock);
	}

	return (vaddr);
}