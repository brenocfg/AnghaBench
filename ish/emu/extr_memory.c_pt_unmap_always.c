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
struct pt_entry {struct data* data; } ;
struct mem {int /*<<< orphan*/  jit; } ;
struct data {scalar_t__ refcount; scalar_t__ data; int /*<<< orphan*/ * fd; int /*<<< orphan*/  size; } ;
typedef  scalar_t__ pages_t ;
typedef  scalar_t__ page_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct data*) ; 
 int /*<<< orphan*/  jit_invalidate_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mem_changed (struct mem*) ; 
 int /*<<< orphan*/  mem_next_page (struct mem*,scalar_t__*) ; 
 struct pt_entry* mem_pt (struct mem*,scalar_t__) ; 
 int /*<<< orphan*/  mem_pt_del (struct mem*,scalar_t__) ; 
 int munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ vdso_data ; 

int pt_unmap_always(struct mem *mem, page_t start, pages_t pages) {
    for (page_t page = start; page < start + pages; mem_next_page(mem, &page)) {
        struct pt_entry *pt = mem_pt(mem, page);
        if (pt == NULL)
            continue;
#if ENGINE_JIT
        jit_invalidate_page(mem->jit, page);
#endif
        struct data *data = pt->data;
        mem_pt_del(mem, page);
        if (--data->refcount == 0) {
            // vdso wasn't allocated with mmap, it's just in our data segment
            if (data->data != vdso_data) {
                int err = munmap(data->data, data->size);
                if (err != 0)
                    die("munmap(%p, %lu) failed: %s", data->data, data->size, strerror(errno));
            }
            if (data->fd != NULL) {
                fd_close(data->fd);
            }
            free(data);
        }
    }
    mem_changed(mem);
    return 0;
}