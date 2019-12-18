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
struct mem {int dummy; } ;
struct fd {int /*<<< orphan*/  real_fd; } ;
typedef  int pages_t ;
typedef  int /*<<< orphan*/  page_t ;
typedef  int off_t ;

/* Variables and functions */
 int MAP_PRIVATE ; 
 int MAP_SHARED ; 
 int MMAP_PRIVATE ; 
 int MMAP_SHARED ; 
 int PAGE_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int P_WRITE ; 
 char* mmap (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int) ; 
 int pt_map (struct mem*,int /*<<< orphan*/ ,int,char*,int,int) ; 
 int real_page_size ; 

int realfs_mmap(struct fd *fd, struct mem *mem, page_t start, pages_t pages, off_t offset, int prot, int flags) {
    if (pages == 0)
        return 0;

    int mmap_flags = 0;
    if (flags & MMAP_PRIVATE) mmap_flags |= MAP_PRIVATE;
    if (flags & MMAP_SHARED) mmap_flags |= MAP_SHARED;
    int mmap_prot = PROT_READ;
    if (prot & P_WRITE) mmap_prot |= PROT_WRITE;

    off_t real_offset = (offset / real_page_size) * real_page_size;
    off_t correction = offset - real_offset;
    char *memory = mmap(NULL, (pages * PAGE_SIZE) + correction,
            mmap_prot, mmap_flags, fd->real_fd, real_offset);
    return pt_map(mem, start, pages, memory, correction, prot);
}