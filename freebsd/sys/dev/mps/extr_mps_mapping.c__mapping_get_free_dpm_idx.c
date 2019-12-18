#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct mps_softc {size_t max_dpm_entries; struct dev_mapping_table* mapping_table; scalar_t__ dpm_pg0; scalar_t__* dpm_entry_used; } ;
struct dev_mapping_table {size_t dpm_entry_num; } ;
struct TYPE_3__ {int High; int Low; } ;
struct TYPE_4__ {size_t MappingInformation; TYPE_1__ PhysicalIdentifier; } ;
typedef  TYPE_2__ Mpi2DriverMap0Entry_t ;
typedef  int /*<<< orphan*/  MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 size_t MPI2_DRVMAP0_MAPINFO_MISSING_MASK ; 
 size_t MPS_DPM_BAD_IDX ; 
 size_t MPS_MAPTABLE_BAD_IDX ; 
 size_t _mapping_get_mt_idx_from_id (struct mps_softc*,int) ; 

__attribute__((used)) static u32
_mapping_get_free_dpm_idx(struct mps_softc *sc)
{
	u16 entry_num;
	Mpi2DriverMap0Entry_t *dpm_entry;
	u16 current_entry = MPS_DPM_BAD_IDX, missing_cnt, high_missing_cnt = 0;
	u64 physical_id;
	struct dev_mapping_table *mt_entry;
	u32 map_idx;

 	for (entry_num = 0; entry_num < sc->max_dpm_entries; entry_num++) {
		dpm_entry = (Mpi2DriverMap0Entry_t *) ((u8 *)sc->dpm_pg0 +
		    sizeof(MPI2_CONFIG_EXTENDED_PAGE_HEADER));
		dpm_entry += entry_num;
		missing_cnt = dpm_entry->MappingInformation &
		    MPI2_DRVMAP0_MAPINFO_MISSING_MASK;

		/*
		 * If entry is used and not missing, then this entry can't be
		 * used. Look at next one.
		 */
		if (sc->dpm_entry_used[entry_num] && !missing_cnt)
			continue;

		/*
		 * If this entry is not used at all, then the missing count
		 * doesn't matter. Just use this one. Otherwise, keep looking
		 * and make sure the entry with the highest missing count is
		 * used.
		 */
		if (!sc->dpm_entry_used[entry_num]) {
			current_entry = entry_num;
			break;
		}
		if ((current_entry == MPS_DPM_BAD_IDX) ||
		    (missing_cnt > high_missing_cnt)) {
			current_entry = entry_num;
			high_missing_cnt = missing_cnt;
		}
 	}

	/*
	 * If an entry has been found to use and it's already marked as used
	 * it means that some device was already using this entry but it's
	 * missing, and that means that the connection between the missing
	 * device's DPM entry and the mapping table needs to be cleared. To do
	 * this, use the Physical ID of the old device still in the DPM entry
	 * to find its mapping table entry, then mark its DPM entry as BAD.
	 */
	if ((current_entry != MPS_DPM_BAD_IDX) &&
	    sc->dpm_entry_used[current_entry]) {
		dpm_entry = (Mpi2DriverMap0Entry_t *) ((u8 *)sc->dpm_pg0 +
		    sizeof(MPI2_CONFIG_EXTENDED_PAGE_HEADER));
		dpm_entry += current_entry;
		physical_id = dpm_entry->PhysicalIdentifier.High;
		physical_id = (physical_id << 32) |
		    dpm_entry->PhysicalIdentifier.Low;
		map_idx = _mapping_get_mt_idx_from_id(sc, physical_id);
		if (map_idx != MPS_MAPTABLE_BAD_IDX) {
			mt_entry = &sc->mapping_table[map_idx];
			mt_entry->dpm_entry_num = MPS_DPM_BAD_IDX;
		}
	}
	return current_entry;
}