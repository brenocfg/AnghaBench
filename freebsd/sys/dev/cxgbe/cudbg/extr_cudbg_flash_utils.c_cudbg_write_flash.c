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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct cudbg_flash_sec_info {int sec_data; int par_sec; int par_sec_offset; scalar_t__ cur_seq_no; } ;
struct cudbg_init {int /*<<< orphan*/  (* print ) (char*,int) ;struct adapter* adap; } ;
struct cudbg_private {struct cudbg_flash_sec_info sec_info; struct cudbg_init dbg_init; } ;
struct cudbg_hdr {int dummy; } ;
struct cudbg_flash_hdr {scalar_t__ data_len; scalar_t__ sec_seq_no; } ;
struct cudbg_entity_hdr {int dummy; } ;
struct cudbg_buffer {int offset; scalar_t__ data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ CUDBG_FLASH_SIZE ; 
 int CUDBG_MAX_ENTITY ; 
 int CUDBG_SF_SECTOR_SIZE ; 
 int CUDBG_STATUS_FLASH_FULL ; 
 int find_empty_sec (struct cudbg_flash_sec_info*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  set_sector_availability (struct cudbg_flash_sec_info*,int,int) ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  update_headers (void*,struct cudbg_buffer*,int /*<<< orphan*/ ,int,int,int) ; 
 int write_flash (struct adapter*,int,int,int) ; 

int cudbg_write_flash(void *handle, u64 timestamp, void *data,
		      u32 start_offset, u32 cur_entity_hdr_offset,
		      u32 cur_entity_size,
		      u32 ext_size)
{
	struct cudbg_private *priv = handle;
	struct cudbg_init *cudbg_init = &priv->dbg_init;
	struct cudbg_flash_sec_info *sec_info = &priv->sec_info;
	struct adapter *adap = cudbg_init->adap;
	struct cudbg_flash_hdr *flash_hdr = NULL;
	struct cudbg_buffer *dbg_buff = (struct cudbg_buffer *)data;
	u32 data_hdr_size;
	u32 total_hdr_size;
	u32 tmp_size;
	u32 sec_data_offset;
	u32 sec_hdr_start_addr;
	u32 sec_data_size;
	u32 space_left;
	int rc = 0;
	int sec;

	data_hdr_size = CUDBG_MAX_ENTITY * sizeof(struct cudbg_entity_hdr) +
			sizeof(struct cudbg_hdr);
	total_hdr_size = data_hdr_size + sizeof(struct cudbg_flash_hdr);
	sec_hdr_start_addr = CUDBG_SF_SECTOR_SIZE - total_hdr_size;
	sec_data_size = sec_hdr_start_addr;

	cudbg_init->print("\tWriting %u bytes to flash\n", cur_entity_size);

	/* this function will get header if sec_info->sec_data does not
	 * have any header and
	 * will update the header if it has header
	 */
	update_headers(handle, dbg_buff, timestamp,
		       cur_entity_hdr_offset,
		       start_offset, ext_size);

	if (ext_size) {
		cur_entity_size += sizeof(struct cudbg_entity_hdr);
		start_offset = dbg_buff->offset - cur_entity_size;
	}

	flash_hdr = (struct cudbg_flash_hdr *)(sec_info->sec_data +
			sec_hdr_start_addr);

	if (flash_hdr->data_len > CUDBG_FLASH_SIZE) {
		rc = CUDBG_STATUS_FLASH_FULL;
		goto out;
	}

	space_left = CUDBG_FLASH_SIZE - flash_hdr->data_len;

	if (cur_entity_size > space_left) {
		rc = CUDBG_STATUS_FLASH_FULL;
		goto out;
	}

	while (cur_entity_size > 0) {
		sec = find_empty_sec(sec_info);
		if (sec_info->par_sec) {
			sec_data_offset = sec_info->par_sec_offset;
			set_sector_availability(sec_info, sec_info->par_sec, 0);
			sec_info->par_sec = 0;
			sec_info->par_sec_offset = 0;

		} else {
			sec_info->cur_seq_no++;
			flash_hdr->sec_seq_no = sec_info->cur_seq_no;
			sec_data_offset = 0;
		}

		if (cur_entity_size + sec_data_offset > sec_data_size) {
			tmp_size = sec_data_size - sec_data_offset;
		} else {
			tmp_size = cur_entity_size;
			sec_info->par_sec = sec;
			sec_info->par_sec_offset = cur_entity_size +
						  sec_data_offset;
		}

		memcpy((void *)((char *)sec_info->sec_data + sec_data_offset),
		       (void *)((char *)dbg_buff->data + start_offset),
		       tmp_size);

		rc = write_flash(adap, sec, sec_info->sec_data,
				CUDBG_SF_SECTOR_SIZE);
		if (rc)
			goto out;

		cur_entity_size -= tmp_size;
		set_sector_availability(sec_info, sec, 1);
		start_offset += tmp_size;
	}
out:
	return rc;
}