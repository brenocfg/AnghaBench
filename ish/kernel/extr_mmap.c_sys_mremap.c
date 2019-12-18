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
struct pt_entry {int flags; } ;
typedef  scalar_t__ pages_t ;
typedef  scalar_t__ page_t ;
typedef  int int_t ;
typedef  int dword_t ;
typedef  int addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int MREMAP_FIXED_ ; 
 int MREMAP_MAYMOVE_ ; 
 scalar_t__ PAGE (int) ; 
 scalar_t__ PGOFFSET (int) ; 
 int P_ANONYMOUS ; 
 int /*<<< orphan*/  STRACE (char*,int,int,int,int) ; 
 int _EFAULT ; 
 int _EINVAL ; 
 int _ENOMEM ; 
 TYPE_1__* current ; 
 struct pt_entry* mem_pt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pt_is_hole (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int pt_map_nothing (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int pt_unmap (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int_t sys_mremap(addr_t addr, dword_t old_len, dword_t new_len, dword_t flags) {
    STRACE("mremap(%#x, %#x, %#x, %d)", addr, old_len, new_len, flags);
    if (PGOFFSET(addr) != 0)
        return _EINVAL;
    if (flags & ~(MREMAP_MAYMOVE_ | MREMAP_FIXED_))
        return _EINVAL;
    if (flags & MREMAP_FIXED_) {
        FIXME("missing MREMAP_FIXED");
        return _EINVAL;
    }
    pages_t old_pages = PAGE(old_len);
    pages_t new_pages = PAGE(new_len);

    // shrinking always works
    if (new_pages <= old_pages) {
        int err = pt_unmap(current->mem, PAGE(addr) + new_pages, old_pages - new_pages);
        if (err < 0)
            return _EFAULT;
        return addr;
    }

    struct pt_entry *entry = mem_pt(current->mem, PAGE(addr));
    if (entry == NULL)
        return _EFAULT;
    dword_t pt_flags = entry->flags;
    for (page_t page = PAGE(addr); page < PAGE(addr) + old_pages; page++) {
        entry = mem_pt(current->mem, page);
        if (entry == NULL && entry->flags != pt_flags)
            return _EFAULT;
    }
    if (!(pt_flags & P_ANONYMOUS)) {
        FIXME("mremap grow on file mappings");
        return _EFAULT;
    }
    page_t extra_start = PAGE(addr) + old_pages;
    pages_t extra_pages = new_pages - old_pages;
    if (!pt_is_hole(current->mem, extra_start, extra_pages))
        return _ENOMEM;
    int err = pt_map_nothing(current->mem, extra_start, extra_pages, pt_flags);
    if (err < 0)
        return err;
    return addr;
}