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
struct unwind_table_entry {unsigned long region_start; unsigned long region_end; } ;
struct unwind_table {int length; struct unwind_table_entry* table; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct unwind_table_entry *
find_unwind_entry_in_table(const struct unwind_table *table, unsigned long addr)
{
	const struct unwind_table_entry *e = NULL;
	unsigned long lo, hi, mid;

	lo = 0; 
	hi = table->length - 1; 
	
	while (lo <= hi) {
		mid = (hi - lo) / 2 + lo;
		e = &table->table[mid];
		if (addr < e->region_start)
			hi = mid - 1;
		else if (addr > e->region_end)
			lo = mid + 1;
		else
			return e;
	}

	return NULL;
}