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
typedef  scalar_t__ uint64_t ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct mpr_softc {size_t max_devices; struct dev_mapping_table* mapping_table; } ;
struct dev_mapping_table {scalar_t__ dev_handle; scalar_t__ physical_id; unsigned int id; } ;

/* Variables and functions */
 unsigned int MPR_MAP_BAD_ID ; 

unsigned int
mpr_mapping_get_tid(struct mpr_softc *sc, uint64_t sas_address, u16 handle)
{
	u32 map_idx;
	struct dev_mapping_table *mt_entry;

	for (map_idx = 0; map_idx < sc->max_devices; map_idx++) {
		mt_entry = &sc->mapping_table[map_idx];
		if (mt_entry->dev_handle == handle && mt_entry->physical_id ==
		    sas_address)
			return mt_entry->id;
	}

	return MPR_MAP_BAD_ID;
}