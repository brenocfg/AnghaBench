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
typedef  scalar_t__ pages_t ;
typedef  scalar_t__ page_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mem_pt (struct mem*,scalar_t__) ; 
 int pt_unmap_always (struct mem*,scalar_t__,scalar_t__) ; 

int pt_unmap(struct mem *mem, page_t start, pages_t pages) {
    for (page_t page = start; page < start + pages; page++)
        if (mem_pt(mem, page) == NULL)
            return -1;
    return pt_unmap_always(mem, start, pages);
}