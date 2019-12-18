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
struct pt_entry {int /*<<< orphan*/ * data; } ;
struct mem {struct pt_entry** pgdir; } ;
typedef  int /*<<< orphan*/  page_t ;

/* Variables and functions */
 size_t PGDIR_BOTTOM (int /*<<< orphan*/ ) ; 
 size_t PGDIR_TOP (int /*<<< orphan*/ ) ; 

struct pt_entry *mem_pt(struct mem *mem, page_t page) {
    struct pt_entry *pgdir = mem->pgdir[PGDIR_TOP(page)];
    if (pgdir == NULL)
        return NULL;
    struct pt_entry *entry = &pgdir[PGDIR_BOTTOM(page)];
    if (entry->data == NULL)
        return NULL;
    return entry;
}