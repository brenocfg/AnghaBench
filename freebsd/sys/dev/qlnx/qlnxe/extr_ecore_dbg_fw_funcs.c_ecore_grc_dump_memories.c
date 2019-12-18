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
typedef  int u8 ;
typedef  size_t u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct dbg_dump_split_hdr {int /*<<< orphan*/  hdr; } ;
struct dbg_array {size_t size_in_dwords; int /*<<< orphan*/ * ptr; } ;
struct TYPE_2__ {size_t size_in_dwords; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 size_t BIN_BUF_DBG_DUMP_MEM ; 
 int /*<<< orphan*/  DBG_DUMP_SPLIT_HDR_DATA_SIZE ; 
 int /*<<< orphan*/  DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 void* GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SPLIT_TYPE_NONE 128 
 size_t ecore_grc_dump_mem_entries (struct ecore_hwfn*,struct ecore_ptt*,struct dbg_array,size_t*,int) ; 
 TYPE_1__* s_dbg_arrays ; 

__attribute__((used)) static u32 ecore_grc_dump_memories(struct ecore_hwfn *p_hwfn,
								   struct ecore_ptt *p_ptt,
								   u32 *dump_buf,
								   bool dump)
{
	u32 offset = 0, input_offset = 0;

	while (input_offset < s_dbg_arrays[BIN_BUF_DBG_DUMP_MEM].size_in_dwords) {
		const struct dbg_dump_split_hdr *split_hdr;
		struct dbg_array curr_input_mems_arr;
		u32 split_data_size;
		u8 split_type_id;

		split_hdr = (const struct dbg_dump_split_hdr *)&s_dbg_arrays[BIN_BUF_DBG_DUMP_MEM].ptr[input_offset++];
		split_type_id = GET_FIELD(split_hdr->hdr, DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID);
		split_data_size = GET_FIELD(split_hdr->hdr, DBG_DUMP_SPLIT_HDR_DATA_SIZE);
		curr_input_mems_arr.ptr = &s_dbg_arrays[BIN_BUF_DBG_DUMP_MEM].ptr[input_offset];
		curr_input_mems_arr.size_in_dwords = split_data_size;

		switch (split_type_id) {
		case SPLIT_TYPE_NONE:
			offset += ecore_grc_dump_mem_entries(p_hwfn, p_ptt, curr_input_mems_arr, dump_buf + offset, dump);
			break;

		default:
			DP_NOTICE(p_hwfn, true, "Dumping split memories is currently not supported\n");
			break;
		}

		input_offset += split_data_size;
	}

	return offset;
}