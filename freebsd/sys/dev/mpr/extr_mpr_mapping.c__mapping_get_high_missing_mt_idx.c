#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  Flags; } ;
struct mpr_softc {int max_devices; struct dev_mapping_table* mapping_table; scalar_t__ ir_firmware; TYPE_1__ ioc_pg8; } ;
struct dev_mapping_table {scalar_t__ missing_count; } ;

/* Variables and functions */
 int MPI2_IOCPAGE8_FLAGS_RESERVED_TARGETID_0 ; 
 int MPR_MAPTABLE_BAD_IDX ; 
 int /*<<< orphan*/  _mapping_get_ir_maprange (struct mpr_softc*,int*,int*) ; 
 int le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
_mapping_get_high_missing_mt_idx(struct mpr_softc *sc)
{
	u32 map_idx, high_idx = MPR_MAPTABLE_BAD_IDX;
	u8 high_missing_count = 0;
	u32 start_idx, end_idx, start_idx_ir, end_idx_ir;
	struct dev_mapping_table *mt_entry;
	u16 ioc_pg8_flags = le16toh(sc->ioc_pg8.Flags);

	start_idx = 0;
	start_idx_ir = 0;
	end_idx_ir = 0;
	end_idx = sc->max_devices;
	if (ioc_pg8_flags & MPI2_IOCPAGE8_FLAGS_RESERVED_TARGETID_0)
		start_idx = 1;
	if (sc->ir_firmware) {
		_mapping_get_ir_maprange(sc, &start_idx_ir, &end_idx_ir);
		if (start_idx == start_idx_ir)
			start_idx = end_idx_ir + 1;
		else
			end_idx = start_idx_ir;
	}
	mt_entry = &sc->mapping_table[start_idx];
	for (map_idx = start_idx; map_idx < end_idx; map_idx++, mt_entry++) {
		if (mt_entry->missing_count > high_missing_count) {
			high_missing_count =  mt_entry->missing_count;
			high_idx = map_idx;
		}
	}
	return high_idx;
}