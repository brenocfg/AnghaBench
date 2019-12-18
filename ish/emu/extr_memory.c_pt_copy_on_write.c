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
struct pt_entry {int flags; int /*<<< orphan*/  offset; TYPE_1__* data; } ;
struct mem {int dummy; } ;
typedef  scalar_t__ page_t ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int P_COMPILED ; 
 int P_COW ; 
 int P_SHARED ; 
 int /*<<< orphan*/  mem_changed (struct mem*) ; 
 int /*<<< orphan*/  mem_next_page (struct mem*,scalar_t__*) ; 
 struct pt_entry* mem_pt (struct mem*,scalar_t__) ; 
 struct pt_entry* mem_pt_new (struct mem*,scalar_t__) ; 
 scalar_t__ pt_unmap_always (struct mem*,scalar_t__,int) ; 

int pt_copy_on_write(struct mem *src, struct mem *dst, page_t start, page_t pages) {
    for (page_t page = start; page < start + pages; mem_next_page(src, &page)) {
        struct pt_entry *entry = mem_pt(src, page);
        if (entry == NULL)
            continue;
        if (pt_unmap_always(dst, page, 1) < 0)
            return -1;
        if (!(entry->flags & P_SHARED))
            entry->flags |= P_COW;
        entry->flags &= ~P_COMPILED;
        entry->data->refcount++;
        struct pt_entry *dst_entry = mem_pt_new(dst, page);
        dst_entry->data = entry->data;
        dst_entry->offset = entry->offset;
        dst_entry->flags = entry->flags;
    }
    mem_changed(src);
    mem_changed(dst);
    return 0;
}