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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct mps_softc {struct dev_mapping_table* mapping_table; } ;
struct dev_mapping_table {scalar_t__ dev_handle; scalar_t__ physical_id; unsigned int id; } ;

/* Variables and functions */
 unsigned int MPS_MAP_BAD_ID ; 
 int /*<<< orphan*/  _mapping_get_ir_maprange (struct mps_softc*,size_t*,size_t*) ; 

unsigned int
mps_mapping_get_raid_tid(struct mps_softc *sc, u64 wwid, u16 volHandle)
{
	u32 start_idx, end_idx, map_idx;
	struct dev_mapping_table *mt_entry;

	_mapping_get_ir_maprange(sc, &start_idx, &end_idx);
	mt_entry = &sc->mapping_table[start_idx];
	for (map_idx  = start_idx; map_idx <= end_idx; map_idx++, mt_entry++) {
		if (mt_entry->dev_handle == volHandle &&
		    mt_entry->physical_id == wwid)
			return mt_entry->id;
	}

	return MPS_MAP_BAD_ID;
}