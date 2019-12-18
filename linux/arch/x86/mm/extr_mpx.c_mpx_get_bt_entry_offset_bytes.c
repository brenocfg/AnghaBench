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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long MPX_BT_NR_ENTRIES_32 ; 
 unsigned long MPX_BT_NR_ENTRIES_64 ; 
 unsigned long bt_entry_size_bytes (struct mm_struct*) ; 
 scalar_t__ is_64bit_mm (struct mm_struct*) ; 

__attribute__((used)) static unsigned long mpx_get_bt_entry_offset_bytes(struct mm_struct *mm,
		unsigned long addr)
{
	unsigned long bt_table_nr_entries;
	unsigned long offset = addr;

	if (is_64bit_mm(mm)) {
		/* Bottom 3 bits are ignored on 64-bit */
		offset >>= 3;
		bt_table_nr_entries = MPX_BT_NR_ENTRIES_64;
	} else {
		/* Bottom 2 bits are ignored on 32-bit */
		offset >>= 2;
		bt_table_nr_entries = MPX_BT_NR_ENTRIES_32;
	}
	/*
	 * We know the size of the table in to which we are
	 * indexing, and we have eliminated all the low bits
	 * which are ignored for indexing.
	 *
	 * Mask out all the high bits which we do not need
	 * to index in to the table.  Note that the tables
	 * are always powers of two so this gives us a proper
	 * mask.
	 */
	offset &= (bt_table_nr_entries-1);
	/*
	 * We now have an entry offset in terms of *entries* in
	 * the table.  We need to scale it back up to bytes.
	 */
	offset *= bt_entry_size_bytes(mm);
	return offset;
}