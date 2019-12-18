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

/* Variables and functions */
 int ENOMEM ; 
 unsigned long _SEGMENT_ENTRY ; 
 unsigned long _SEGMENT_ENTRY_INVALID ; 
 unsigned long _SEGMENT_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_INDEX ; 
 unsigned long _SEGMENT_SHIFT ; 
 int base_page_walk (unsigned long,unsigned long,unsigned long,int) ; 
 unsigned long base_pgt_alloc () ; 
 int /*<<< orphan*/  base_pgt_free (unsigned long) ; 
 unsigned long base_segment_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 

__attribute__((used)) static int base_segment_walk(unsigned long origin, unsigned long addr,
			     unsigned long end, int alloc)
{
	unsigned long *ste, next, table;
	int rc;

	ste = (unsigned long *) origin;
	ste += (addr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
	do {
		next = base_segment_addr_end(addr, end);
		if (*ste & _SEGMENT_ENTRY_INVALID) {
			if (!alloc)
				continue;
			table = base_pgt_alloc();
			if (!table)
				return -ENOMEM;
			*ste = table | _SEGMENT_ENTRY;
		}
		table = *ste & _SEGMENT_ENTRY_ORIGIN;
		rc = base_page_walk(table, addr, next, alloc);
		if (rc)
			return rc;
		if (!alloc)
			base_pgt_free(table);
		cond_resched();
	} while (ste++, addr = next, addr < end);
	return 0;
}