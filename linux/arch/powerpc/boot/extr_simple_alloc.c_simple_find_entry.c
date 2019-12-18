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
struct alloc_info {int flags; unsigned long base; } ;

/* Variables and functions */
 int ENTRY_BEEN_USED ; 
 int ENTRY_IN_USE ; 
 struct alloc_info* alloc_tbl ; 
 unsigned long tbl_entries ; 

__attribute__((used)) static struct alloc_info *simple_find_entry(void *ptr)
{
	unsigned long i;
	struct alloc_info *p = alloc_tbl;

	for (i=0; i<tbl_entries; i++,p++) {
		if (!(p->flags & ENTRY_BEEN_USED))
			break;
		if ((p->flags & ENTRY_IN_USE) &&
		    (p->base == (unsigned long)ptr))
			return p;
	}
	return NULL;
}