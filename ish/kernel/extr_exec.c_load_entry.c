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
struct prg_header {scalar_t__ vaddr; scalar_t__ offset; scalar_t__ memsize; scalar_t__ filesize; int flags; } ;
struct fd {TYPE_1__* ops; } ;
typedef  scalar_t__ dword_t ;
typedef  scalar_t__ addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  mem; } ;
struct TYPE_7__ {TYPE_2__* data; } ;
struct TYPE_6__ {scalar_t__ file_offset; int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int (* mmap ) (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MMAP_PRIVATE ; 
 int /*<<< orphan*/  PAGE (scalar_t__) ; 
 int /*<<< orphan*/  PAGE_ROUND_UP (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PGOFFSET (scalar_t__) ; 
 int PH_W ; 
 int P_READ ; 
 int P_WRITE ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  fd_retain (struct fd*) ; 
 TYPE_3__* mem_pt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pt_map_nothing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int load_entry(struct prg_header ph, addr_t bias, struct fd *fd) {
    int err;

    addr_t addr = ph.vaddr + bias;
    addr_t offset = ph.offset;
    addr_t memsize = ph.memsize;
    addr_t filesize = ph.filesize;

    int flags = P_READ;
    if (ph.flags & PH_W) flags |= P_WRITE;

    if ((err = fd->ops->mmap(fd, current->mem, PAGE(addr),
                    PAGE_ROUND_UP(filesize + PGOFFSET(addr)),
                    offset - PGOFFSET(addr), flags, MMAP_PRIVATE)) < 0)
        return err;
    // TODO find a better place for these to avoid code duplication
    mem_pt(current->mem, PAGE(addr))->data->fd = fd_retain(fd);
    mem_pt(current->mem, PAGE(addr))->data->file_offset = offset - PGOFFSET(addr);

    if (memsize > filesize) {
        // put zeroes between addr + filesize and addr + memsize, call that bss
        dword_t bss_size = memsize - filesize;

        // first zero the tail from the end of the file mapping to the end
        // of the load entry or the end of the page, whichever comes first
        addr_t file_end = addr + filesize;
        dword_t tail_size = PAGE_SIZE - PGOFFSET(file_end);
        if (tail_size == PAGE_SIZE)
            // if you can calculate tail_size better and not have to do this please let me know
            tail_size = 0;

        if (tail_size != 0)
            user_memset(file_end, 0, tail_size);
        if (tail_size > bss_size)
            tail_size = bss_size;

        // then map the pages from after the file mapping up to and including the end of bss
        if (bss_size - tail_size != 0)
            if ((err = pt_map_nothing(current->mem, PAGE_ROUND_UP(addr + filesize),
                    PAGE_ROUND_UP(bss_size - tail_size), flags)) < 0)
                return err;
    }
    return 0;
}