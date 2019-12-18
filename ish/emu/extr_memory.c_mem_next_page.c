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
struct mem {int /*<<< orphan*/ ** pgdir; } ;
typedef  scalar_t__ page_t ;

/* Variables and functions */
 scalar_t__ MEM_PAGES ; 
 scalar_t__ MEM_PGDIR_SIZE ; 
 scalar_t__ PGDIR_BOTTOM (scalar_t__) ; 
 size_t PGDIR_TOP (scalar_t__) ; 

void mem_next_page(struct mem *mem, page_t *page) {
    (*page)++;
    if (*page >= MEM_PAGES)
        return;
    while (*page < MEM_PAGES && mem->pgdir[PGDIR_TOP(*page)] == NULL)
        *page = (*page - PGDIR_BOTTOM(*page)) + MEM_PGDIR_SIZE;
}