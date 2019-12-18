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
 unsigned long PAGE_SIZE ; 
 unsigned long _ASCE_TABLE_LENGTH ; 
 unsigned long _ASCE_TYPE_REGION1 ; 
 unsigned long _ASCE_TYPE_REGION2 ; 
 unsigned long _ASCE_TYPE_REGION3 ; 
 unsigned long _ASCE_TYPE_SEGMENT ; 
 int /*<<< orphan*/  _REGION1_ENTRY_EMPTY ; 
 unsigned long _REGION1_SIZE ; 
 int /*<<< orphan*/  _REGION2_ENTRY_EMPTY ; 
 unsigned long _REGION2_SIZE ; 
 int /*<<< orphan*/  _REGION3_ENTRY_EMPTY ; 
 unsigned long _REGION3_SIZE ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_EMPTY ; 
 int /*<<< orphan*/  base_asce_free (unsigned long) ; 
 unsigned long base_crst_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ base_pgt_cache_init () ; 
 int base_region1_walk (unsigned long,unsigned long,unsigned long,int) ; 
 int base_region2_walk (unsigned long,unsigned long,unsigned long,int) ; 
 int base_region3_walk (unsigned long,unsigned long,unsigned long,int) ; 
 int base_segment_walk (unsigned long,unsigned long,unsigned long,int) ; 

unsigned long base_asce_alloc(unsigned long addr, unsigned long num_pages)
{
	unsigned long asce, table, end;
	int rc;

	if (base_pgt_cache_init())
		return 0;
	end = addr + num_pages * PAGE_SIZE;
	if (end <= _REGION3_SIZE) {
		table = base_crst_alloc(_SEGMENT_ENTRY_EMPTY);
		if (!table)
			return 0;
		rc = base_segment_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_SEGMENT | _ASCE_TABLE_LENGTH;
	} else if (end <= _REGION2_SIZE) {
		table = base_crst_alloc(_REGION3_ENTRY_EMPTY);
		if (!table)
			return 0;
		rc = base_region3_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_REGION3 | _ASCE_TABLE_LENGTH;
	} else if (end <= _REGION1_SIZE) {
		table = base_crst_alloc(_REGION2_ENTRY_EMPTY);
		if (!table)
			return 0;
		rc = base_region2_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_REGION2 | _ASCE_TABLE_LENGTH;
	} else {
		table = base_crst_alloc(_REGION1_ENTRY_EMPTY);
		if (!table)
			return 0;
		rc = base_region1_walk(table, addr, end, 1);
		asce = table | _ASCE_TYPE_REGION1 | _ASCE_TABLE_LENGTH;
	}
	if (rc) {
		base_asce_free(asce);
		asce = 0;
	}
	return asce;
}