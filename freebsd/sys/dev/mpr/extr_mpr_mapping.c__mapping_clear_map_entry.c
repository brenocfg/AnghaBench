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
typedef  scalar_t__ u8 ;
struct dev_mapping_table {int id; scalar_t__ TLR_bits; scalar_t__ init_complete; scalar_t__ missing_count; scalar_t__ dev_handle; int /*<<< orphan*/  dpm_entry_num; scalar_t__ phy_bits; scalar_t__ device_info; scalar_t__ physical_id; } ;

/* Variables and functions */
 scalar_t__ MPI2_SCSIIO_CONTROL_NO_TLR ; 
 int /*<<< orphan*/  MPR_DPM_BAD_IDX ; 

__attribute__((used)) static inline void
_mapping_clear_map_entry(struct dev_mapping_table *map_entry)
{
	map_entry->physical_id = 0;
	map_entry->device_info = 0;
	map_entry->phy_bits = 0;
	map_entry->dpm_entry_num = MPR_DPM_BAD_IDX;
	map_entry->dev_handle = 0;
	map_entry->id = -1;
	map_entry->missing_count = 0;
	map_entry->init_complete = 0;
	map_entry->TLR_bits = (u8)MPI2_SCSIIO_CONTROL_NO_TLR;
}