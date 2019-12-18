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
struct unw_table_entry {unsigned long start_offset; unsigned long end_offset; } ;
struct unw_table {unsigned long length; struct unw_table_entry* array; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct unw_table_entry *
lookup (struct unw_table *table, unsigned long rel_ip)
{
	const struct unw_table_entry *e = NULL;
	unsigned long lo, hi, mid;

	/* do a binary search for right entry: */
	for (lo = 0, hi = table->length; lo < hi; ) {
		mid = (lo + hi) / 2;
		e = &table->array[mid];
		if (rel_ip < e->start_offset)
			hi = mid;
		else if (rel_ip >= e->end_offset)
			lo = mid + 1;
		else
			break;
	}
	if (rel_ip < e->start_offset || rel_ip >= e->end_offset)
		return NULL;
	return e;
}