#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fd {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  pages_t ;
typedef  scalar_t__ page_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  scalar_t__ addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  mem; } ;
struct TYPE_7__ {TYPE_2__* data; } ;
struct TYPE_6__ {int file_offset; int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int (* mmap ) (struct fd*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 scalar_t__ BAD_PAGE ; 
 int MMAP_ANONYMOUS ; 
 int MMAP_FIXED ; 
 int MMAP_SHARED ; 
 scalar_t__ PAGE (scalar_t__) ; 
 scalar_t__ PAGE_BITS ; 
 int /*<<< orphan*/  PAGE_ROUND_UP (int) ; 
 scalar_t__ PGOFFSET (scalar_t__) ; 
 int P_SHARED ; 
 scalar_t__ _EBADF ; 
 scalar_t__ _EINVAL ; 
 scalar_t__ _ENODEV ; 
 scalar_t__ _ENOMEM ; 
 TYPE_4__* current ; 
 struct fd* f_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_retain (struct fd*) ; 
 TYPE_3__* mem_pt (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pt_find_hole (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_is_hole (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int pt_map_nothing (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct fd*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static addr_t do_mmap(addr_t addr, dword_t len, dword_t prot, dword_t flags, fd_t fd_no, dword_t offset) {
    int err;
    pages_t pages = PAGE_ROUND_UP(len);
    page_t page;
    if (addr != 0) {
        if (PGOFFSET(addr) != 0)
            return _EINVAL;
        page = PAGE(addr);
        if (!(flags & MMAP_FIXED) && !pt_is_hole(current->mem, page, pages)) {
            addr = 0;
        }
    }
    if (addr == 0) {
        page = pt_find_hole(current->mem, pages);
        if (page == BAD_PAGE)
            return _ENOMEM;
    }

    if (flags & MMAP_SHARED)
        prot |= P_SHARED;

    if (flags & MMAP_ANONYMOUS) {
        if ((err = pt_map_nothing(current->mem, page, pages, prot)) < 0)
            return err;
    } else {
        // fd must be valid
        struct fd *fd = f_get(fd_no);
        if (fd == NULL)
            return _EBADF;
        if (fd->ops->mmap == NULL)
            return _ENODEV;
        if ((err = fd->ops->mmap(fd, current->mem, page, pages, offset, prot, flags)) < 0)
            return err;
        mem_pt(current->mem, page)->data->fd = fd_retain(fd);
        mem_pt(current->mem, page)->data->file_offset = offset;
    }
    return page << PAGE_BITS;
}