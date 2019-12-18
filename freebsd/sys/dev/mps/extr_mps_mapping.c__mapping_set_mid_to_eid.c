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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct mps_softc {struct dev_mapping_table* mapping_table; } ;
struct enc_mapping_table {scalar_t__ num_slots; size_t start_index; int /*<<< orphan*/  enclosure_id; } ;
struct dev_mapping_table {int /*<<< orphan*/  physical_id; } ;

/* Variables and functions */
 size_t MPS_MAPTABLE_BAD_IDX ; 

__attribute__((used)) static inline void
_mapping_set_mid_to_eid(struct mps_softc *sc,
    struct enc_mapping_table *et_entry)
{
	struct dev_mapping_table *mt_entry;
	u16 slots = et_entry->num_slots, map_idx;
	u32 start_idx = et_entry->start_index;

	if (start_idx != MPS_MAPTABLE_BAD_IDX) {
		mt_entry = &sc->mapping_table[start_idx];
		for (map_idx = 0; map_idx < slots; map_idx++, mt_entry++)
			mt_entry->physical_id = et_entry->enclosure_id;
	}
}