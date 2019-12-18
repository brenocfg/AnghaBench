#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct raid_map {scalar_t__ parity_rotation_shift; int phys_blk_shift; int /*<<< orphan*/  flags; int /*<<< orphan*/  disk_starting_blk; TYPE_1__* dev_data; int /*<<< orphan*/  row_cnt; int /*<<< orphan*/  metadata_disks_per_row; int /*<<< orphan*/  layout_map_count; int /*<<< orphan*/  strip_size; int /*<<< orphan*/  data_disks_per_row; int /*<<< orphan*/  volume_blk_cnt; } ;
struct TYPE_8__ {int cmdlen; int encrypt_enable; int /*<<< orphan*/  enc_info; int /*<<< orphan*/  ioaccel_handle; } ;
typedef  TYPE_2__ rcb_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_9__ {scalar_t__ raid_level; int offload_to_mirror; struct raid_map* raid_map; } ;
typedef  TYPE_3__ pqi_scsi_dev_t ;
typedef  int boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  ioaccel_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_IO (char*,...) ; 
 int GET_LE16 (int*) ; 
 scalar_t__ GET_LE64 (int*) ; 
 int /*<<< orphan*/  OS_GET_CDBP (TYPE_2__*) ; 
 scalar_t__ PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  PUT_BE16 (scalar_t__,int*) ; 
 int /*<<< orphan*/  PUT_BE32 (scalar_t__,int*) ; 
 int /*<<< orphan*/  PUT_BE64 (scalar_t__,int*) ; 
 int RAID_MAP_ENCRYPTION_ENABLED ; 
 scalar_t__ RAID_MAP_MAX_ENTRIES ; 
 scalar_t__ SA_RAID_0 ; 
 scalar_t__ SA_RAID_1 ; 
 scalar_t__ SA_RAID_5 ; 
 scalar_t__ SA_RAID_6 ; 
 scalar_t__ SA_RAID_ADM ; 
 int SCMD_READ_10 ; 
 int SCMD_READ_16 ; 
 int SCMD_WRITE_10 ; 
 int SCMD_WRITE_16 ; 
 scalar_t__ check_for_scsi_opcode (int*,int*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pqisrc_set_enc_info (int /*<<< orphan*/ *,struct raid_map*,scalar_t__) ; 

int pqisrc_send_scsi_cmd_raidbypass(pqisrc_softstate_t *softs,
				pqi_scsi_dev_t *device, rcb_t *rcb, uint8_t *cdb)
{
	struct raid_map *raid_map;
	boolean_t is_write = false;
	uint32_t map_idx;
	uint64_t fst_blk, lst_blk;
	uint32_t blk_cnt, blks_per_row;
	uint64_t fst_row, lst_row;
	uint32_t fst_row_offset, lst_row_offset;
	uint32_t fst_col, lst_col;
	uint32_t r5or6_blks_per_row;
	uint64_t r5or6_fst_row, r5or6_lst_row;
	uint32_t r5or6_fst_row_offset, r5or6_lst_row_offset;
	uint32_t r5or6_fst_col, r5or6_lst_col;
	uint16_t data_disks_per_row, total_disks_per_row;
	uint16_t layout_map_count;
	uint32_t stripesz;
	uint16_t strip_sz;
	uint32_t fst_grp, lst_grp, cur_grp;
	uint32_t map_row;
	uint64_t disk_block;
	uint32_t disk_blk_cnt;
	uint8_t cdb_length;
	int offload_to_mirror;
	int i;
	DBG_FUNC(" IN \n");
	DBG_IO("!!!!!\n");

	/* Check for eligible opcode, get LBA and block count. */
	memcpy(cdb, OS_GET_CDBP(rcb), rcb->cmdlen);
	
	for(i = 0; i < rcb->cmdlen ; i++)
		DBG_IO(" CDB [ %d ] : %x\n",i,cdb[i]);
	if(check_for_scsi_opcode(cdb, &is_write, 
		&fst_blk, &blk_cnt) == PQI_STATUS_FAILURE)
			return PQI_STATUS_FAILURE;
	/* Check for write to non-RAID-0. */
	if (is_write && device->raid_level != SA_RAID_0)
		return PQI_STATUS_FAILURE;;

	if(blk_cnt == 0) 
		return PQI_STATUS_FAILURE;

	lst_blk = fst_blk + blk_cnt - 1;
	raid_map = device->raid_map;

	/* Check for invalid block or wraparound. */
	if (lst_blk >= GET_LE64((uint8_t *)&raid_map->volume_blk_cnt) ||
		lst_blk < fst_blk)
		return PQI_STATUS_FAILURE;

	data_disks_per_row = GET_LE16((uint8_t *)&raid_map->data_disks_per_row);
	strip_sz = GET_LE16((uint8_t *)(&raid_map->strip_size));
	layout_map_count = GET_LE16((uint8_t *)(&raid_map->layout_map_count));

	/* Calculate stripe information for the request. */
	blks_per_row = data_disks_per_row * strip_sz;
	if (!blks_per_row)
		return PQI_STATUS_FAILURE;
	/* use __udivdi3 ? */
	fst_row = fst_blk / blks_per_row;
	lst_row = lst_blk / blks_per_row;
	fst_row_offset = (uint32_t)(fst_blk - (fst_row * blks_per_row));
	lst_row_offset = (uint32_t)(lst_blk - (lst_row * blks_per_row));
	fst_col = fst_row_offset / strip_sz;
	lst_col = lst_row_offset / strip_sz;

	/* If this isn't a single row/column then give to the controller. */
	if (fst_row != lst_row || fst_col != lst_col)
		return PQI_STATUS_FAILURE;

	/* Proceeding with driver mapping. */
	total_disks_per_row = data_disks_per_row +
		GET_LE16((uint8_t *)(&raid_map->metadata_disks_per_row));
	map_row = ((uint32_t)(fst_row >> raid_map->parity_rotation_shift)) %
		GET_LE16((uint8_t *)(&raid_map->row_cnt));
	map_idx = (map_row * total_disks_per_row) + fst_col;

	/* RAID 1 */
	if (device->raid_level == SA_RAID_1) {
		if (device->offload_to_mirror)
			map_idx += data_disks_per_row;
		device->offload_to_mirror = !device->offload_to_mirror;
	} else if (device->raid_level == SA_RAID_ADM) {
		/* RAID ADM */
		/*
		 * Handles N-way mirrors  (R1-ADM) and R10 with # of drives
		 * divisible by 3.
		 */
		offload_to_mirror = device->offload_to_mirror;
		if (offload_to_mirror == 0)  {
			/* use physical disk in the first mirrored group. */
			map_idx %= data_disks_per_row;
		} else {
			do {
				/*
				 * Determine mirror group that map_idx
				 * indicates.
				 */
				cur_grp = map_idx / data_disks_per_row;

				if (offload_to_mirror != cur_grp) {
					if (cur_grp <
						layout_map_count - 1) {
						/*
						 * Select raid index from
						 * next group.
						 */
						map_idx += data_disks_per_row;
						cur_grp++;
					} else {
						/*
						 * Select raid index from first
						 * group.
						 */
						map_idx %= data_disks_per_row;
						cur_grp = 0;
					}
				}
			} while (offload_to_mirror != cur_grp);
		}

		/* Set mirror group to use next time. */
		offload_to_mirror =
			(offload_to_mirror >= layout_map_count - 1) ?
				0 : offload_to_mirror + 1;
		if(offload_to_mirror >= layout_map_count)
			return PQI_STATUS_FAILURE;

		device->offload_to_mirror = offload_to_mirror;
		/*
		 * Avoid direct use of device->offload_to_mirror within this
		 * function since multiple threads might simultaneously
		 * increment it beyond the range of device->layout_map_count -1.
		 */
	} else if ((device->raid_level == SA_RAID_5 ||
		device->raid_level == SA_RAID_6) && layout_map_count > 1) {
		/* RAID 50/60 */
		/* Verify first and last block are in same RAID group */
		r5or6_blks_per_row = strip_sz * data_disks_per_row;
		stripesz = r5or6_blks_per_row * layout_map_count;

		fst_grp = (fst_blk % stripesz) / r5or6_blks_per_row;
		lst_grp = (lst_blk % stripesz) / r5or6_blks_per_row;

		if (fst_grp != lst_grp)
			return PQI_STATUS_FAILURE;

		/* Verify request is in a single row of RAID 5/6 */
		fst_row = r5or6_fst_row =
			fst_blk / stripesz;
		r5or6_lst_row = lst_blk / stripesz;

		if (r5or6_fst_row != r5or6_lst_row)
			return PQI_STATUS_FAILURE;

		/* Verify request is in a single column */
		fst_row_offset = r5or6_fst_row_offset =
			(uint32_t)((fst_blk % stripesz) %
			r5or6_blks_per_row);

		r5or6_lst_row_offset =
			(uint32_t)((lst_blk % stripesz) %
			r5or6_blks_per_row);

		fst_col = r5or6_fst_row_offset / strip_sz;
		r5or6_fst_col = fst_col;
		r5or6_lst_col = r5or6_lst_row_offset / strip_sz;

		if (r5or6_fst_col != r5or6_lst_col)
			return PQI_STATUS_FAILURE;

		/* Request is eligible */
		map_row =
			((uint32_t)(fst_row >> raid_map->parity_rotation_shift)) %
			GET_LE16((uint8_t *)(&raid_map->row_cnt));

		map_idx = (fst_grp *
			(GET_LE16((uint8_t *)(&raid_map->row_cnt)) *
			total_disks_per_row)) +
			(map_row * total_disks_per_row) + fst_col;
	}

	if (map_idx >= RAID_MAP_MAX_ENTRIES)
		return PQI_STATUS_FAILURE;

	rcb->ioaccel_handle = raid_map->dev_data[map_idx].ioaccel_handle;
	disk_block = GET_LE64((uint8_t *)(&raid_map->disk_starting_blk)) +
		fst_row * strip_sz +
		(fst_row_offset - fst_col * strip_sz);
	disk_blk_cnt = blk_cnt;

	/* Handle differing logical/physical block sizes. */
	if (raid_map->phys_blk_shift) {
		disk_block <<= raid_map->phys_blk_shift;
		disk_blk_cnt <<= raid_map->phys_blk_shift;
	}

	if (disk_blk_cnt > 0xffff)
		return PQI_STATUS_FAILURE;

	/* Build the new CDB for the physical disk I/O. */
	if (disk_block > 0xffffffff) {
		cdb[0] = is_write ? SCMD_WRITE_16 : SCMD_READ_16;
		cdb[1] = 0;
		PUT_BE64(disk_block, &cdb[2]);
		PUT_BE32(disk_blk_cnt, &cdb[10]);
		cdb[14] = 0;
		cdb[15] = 0;
		cdb_length = 16;
	} else {
		cdb[0] = is_write ? SCMD_WRITE_10 : SCMD_READ_10;
		cdb[1] = 0;
		PUT_BE32(disk_block, &cdb[2]);
		cdb[6] = 0;
		PUT_BE16(disk_blk_cnt, &cdb[7]);
		cdb[9] = 0;
		cdb_length = 10;
	}

	if (GET_LE16((uint8_t *)(&raid_map->flags)) &
		RAID_MAP_ENCRYPTION_ENABLED) {
		pqisrc_set_enc_info(&rcb->enc_info, raid_map,
			fst_blk);
		rcb->encrypt_enable = true;
	} else {
		rcb->encrypt_enable = false;
	}

	rcb->cmdlen = cdb_length;
	
		
	DBG_FUNC("OUT");
	
	return PQI_STATUS_SUCCESS;
}