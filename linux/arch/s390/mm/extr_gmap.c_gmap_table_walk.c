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
struct gmap {int asce; unsigned long* table; scalar_t__ removed; } ;

/* Variables and functions */
 int _ASCE_TYPE_MASK ; 
#define  _ASCE_TYPE_REGION1 131 
#define  _ASCE_TYPE_REGION2 130 
#define  _ASCE_TYPE_REGION3 129 
#define  _ASCE_TYPE_SEGMENT 128 
 unsigned long _PAGE_INDEX ; 
 unsigned long _PAGE_SHIFT ; 
 unsigned long _REGION1_INDEX ; 
 unsigned long _REGION1_SHIFT ; 
 unsigned long _REGION2_INDEX ; 
 unsigned long _REGION2_SHIFT ; 
 unsigned long _REGION3_INDEX ; 
 unsigned long _REGION3_SHIFT ; 
 unsigned long _REGION_ENTRY_INVALID ; 
 unsigned long _REGION_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_INDEX ; 
 unsigned long _SEGMENT_SHIFT ; 
 scalar_t__ gmap_is_shadow (struct gmap*) ; 

__attribute__((used)) static inline unsigned long *gmap_table_walk(struct gmap *gmap,
					     unsigned long gaddr, int level)
{
	unsigned long *table;

	if ((gmap->asce & _ASCE_TYPE_MASK) + 4 < (level * 4))
		return NULL;
	if (gmap_is_shadow(gmap) && gmap->removed)
		return NULL;
	if (gaddr & (-1UL << (31 + ((gmap->asce & _ASCE_TYPE_MASK) >> 2)*11)))
		return NULL;
	table = gmap->table;
	switch (gmap->asce & _ASCE_TYPE_MASK) {
	case _ASCE_TYPE_REGION1:
		table += (gaddr & _REGION1_INDEX) >> _REGION1_SHIFT;
		if (level == 4)
			break;
		if (*table & _REGION_ENTRY_INVALID)
			return NULL;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
		/* Fallthrough */
	case _ASCE_TYPE_REGION2:
		table += (gaddr & _REGION2_INDEX) >> _REGION2_SHIFT;
		if (level == 3)
			break;
		if (*table & _REGION_ENTRY_INVALID)
			return NULL;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
		/* Fallthrough */
	case _ASCE_TYPE_REGION3:
		table += (gaddr & _REGION3_INDEX) >> _REGION3_SHIFT;
		if (level == 2)
			break;
		if (*table & _REGION_ENTRY_INVALID)
			return NULL;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
		/* Fallthrough */
	case _ASCE_TYPE_SEGMENT:
		table += (gaddr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
		if (level == 1)
			break;
		if (*table & _REGION_ENTRY_INVALID)
			return NULL;
		table = (unsigned long *)(*table & _SEGMENT_ENTRY_ORIGIN);
		table += (gaddr & _PAGE_INDEX) >> _PAGE_SHIFT;
	}
	return table;
}