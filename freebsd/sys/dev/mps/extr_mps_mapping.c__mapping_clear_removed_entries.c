#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  Flags; } ;
struct mps_softc {scalar_t__ max_devices; int* dpm_flush_entry; int num_enc_table_entries; struct enc_mapping_table* enclosure_table; scalar_t__* dpm_entry_used; scalar_t__ dpm_pg0; struct map_removal_table* removal_table; scalar_t__ is_dpm_enable; TYPE_1__ ioc_pg8; } ;
struct map_removal_table {size_t dpm_entry_num; } ;
struct enc_mapping_table {scalar_t__ init_complete; int /*<<< orphan*/  enc_handle; } ;
struct TYPE_5__ {scalar_t__ High; scalar_t__ Low; } ;
struct TYPE_6__ {scalar_t__ PhysicalBitsMapping; scalar_t__ MappingInformation; scalar_t__ DeviceIndex; TYPE_2__ PhysicalIdentifier; } ;
typedef  TYPE_3__ Mpi2DriverMap0Entry_t ;
typedef  int /*<<< orphan*/  MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int MPI2_IOCPAGE8_FLAGS_ENCLOSURE_SLOT_MAPPING ; 
 int MPI2_IOCPAGE8_FLAGS_MASK_MAPPING_MODE ; 
 size_t MPS_DPM_BAD_IDX ; 
 int /*<<< orphan*/  _mapping_clear_enc_entry (struct enc_mapping_table*) ; 
 int /*<<< orphan*/  _mapping_set_mid_to_eid (struct mps_softc*,struct enc_mapping_table*) ; 
 int le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_mapping_clear_removed_entries(struct mps_softc *sc)
{
	u32 remove_idx;
	struct map_removal_table *remove_entry;
	Mpi2DriverMap0Entry_t *dpm_entry;
	u8 done_flag = 0, num_entries, m, i;
	struct enc_mapping_table *et_entry, *from, *to;
	u16 ioc_pg8_flags = le16toh(sc->ioc_pg8.Flags);

	if (sc->is_dpm_enable) {
		remove_entry = sc->removal_table;
		for (remove_idx = 0; remove_idx < sc->max_devices;
		    remove_idx++, remove_entry++) {
			if (remove_entry->dpm_entry_num != MPS_DPM_BAD_IDX) {
				dpm_entry = (Mpi2DriverMap0Entry_t *)
				    ((u8 *) sc->dpm_pg0 +
				    sizeof(MPI2_CONFIG_EXTENDED_PAGE_HEADER));
				dpm_entry += remove_entry->dpm_entry_num;
				dpm_entry->PhysicalIdentifier.Low = 0;
				dpm_entry->PhysicalIdentifier.High = 0;
				dpm_entry->DeviceIndex = 0;
				dpm_entry->MappingInformation = 0;
				dpm_entry->PhysicalBitsMapping = 0;
				sc->dpm_flush_entry[remove_entry->
				    dpm_entry_num] = 1;
				sc->dpm_entry_used[remove_entry->dpm_entry_num]
				    = 0;
				remove_entry->dpm_entry_num = MPS_DPM_BAD_IDX;
			}
		}
	}

	/*
	 * When using Enc/Slot mapping, if a new enclosure was added and old
	 * enclosure space was needed, the enclosure table may now have gaps
	 * that need to be closed. All enclosure mappings need to be contiguous
	 * so that space can be reused correctly if available.
	 */
	if ((ioc_pg8_flags & MPI2_IOCPAGE8_FLAGS_MASK_MAPPING_MODE) ==
	    MPI2_IOCPAGE8_FLAGS_ENCLOSURE_SLOT_MAPPING) {
		num_entries = sc->num_enc_table_entries;
		while (!done_flag) {
			done_flag = 1;
			et_entry = sc->enclosure_table;
			for (i = 0; i < num_entries; i++, et_entry++) {
				if (!et_entry->enc_handle && et_entry->
				    init_complete) {
					done_flag = 0;
					if (i != (num_entries - 1)) {
						from = &sc->enclosure_table
						    [i+1];
						to = &sc->enclosure_table[i];
						for (m = i; m < (num_entries -
						    1); m++, from++, to++) {
							_mapping_set_mid_to_eid
							    (sc, to);
							*to = *from;
						}
						_mapping_clear_enc_entry(to);
						sc->num_enc_table_entries--;
						num_entries =
						    sc->num_enc_table_entries;
					} else {
						_mapping_clear_enc_entry
						    (et_entry);
						sc->num_enc_table_entries--;
						num_entries =
						    sc->num_enc_table_entries;
					}
				}
			}
		}
	}
}