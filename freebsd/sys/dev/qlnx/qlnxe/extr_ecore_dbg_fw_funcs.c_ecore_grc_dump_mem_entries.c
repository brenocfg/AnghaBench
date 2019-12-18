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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  void* u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct dbg_dump_mem {int /*<<< orphan*/  dword1; int /*<<< orphan*/  dword0; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct dbg_dump_cond_hdr {size_t data_size; size_t block_id; TYPE_1__ mode; } ;
struct dbg_array {size_t size_in_dwords; int /*<<< orphan*/ * ptr; } ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;
struct TYPE_6__ {size_t storm_id; scalar_t__ associated_to_storm; } ;
struct TYPE_5__ {char letter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DUMP_MEM_ADDRESS ; 
 int /*<<< orphan*/  DBG_DUMP_MEM_LENGTH ; 
 int /*<<< orphan*/  DBG_DUMP_MEM_MEM_GROUP_ID ; 
 int /*<<< orphan*/  DBG_DUMP_MEM_WIDE_BUS ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_NUM_LCIDS ; 
 int /*<<< orphan*/  DBG_GRC_PARAM_NUM_LTIDS ; 
 int /*<<< orphan*/  DBG_MODE_HDR_EVAL_MODE ; 
 int /*<<< orphan*/  DBG_MODE_HDR_MODES_BUF_OFFSET ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 void* GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MAX_LCIDS ; 
 size_t MAX_LTIDS ; 
 size_t MEM_DUMP_ENTRY_SIZE_DWORDS ; 
 size_t MEM_GROUPS_NUM ; 
 size_t MEM_GROUP_CONN_CFC_MEM ; 
 size_t MEM_GROUP_TASK_CFC_MEM ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 size_t ecore_grc_dump_mem (struct ecore_hwfn*,struct ecore_ptt*,size_t*,int,int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char) ; 
 size_t ecore_grc_get_param (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_grc_is_mem_included (struct ecore_hwfn*,int,size_t) ; 
 int ecore_is_mode_match (struct ecore_hwfn*,void**) ; 
 TYPE_3__** s_block_defs ; 
 int /*<<< orphan*/ * s_mem_group_names ; 
 TYPE_2__* s_storm_defs ; 

__attribute__((used)) static u32 ecore_grc_dump_mem_entries(struct ecore_hwfn *p_hwfn,
									  struct ecore_ptt *p_ptt,
									  struct dbg_array input_mems_arr,
									  u32 *dump_buf,
									  bool dump)
{
	u32 i, offset = 0, input_offset = 0;
	bool mode_match = true;

	while (input_offset < input_mems_arr.size_in_dwords) {
		const struct dbg_dump_cond_hdr *cond_hdr;
		u16 modes_buf_offset;
		u32 num_entries;
		bool eval_mode;

		cond_hdr = (const struct dbg_dump_cond_hdr *)&input_mems_arr.ptr[input_offset++];
		num_entries = cond_hdr->data_size / MEM_DUMP_ENTRY_SIZE_DWORDS;

		/* Check required mode */
		eval_mode = GET_FIELD(cond_hdr->mode.data, DBG_MODE_HDR_EVAL_MODE) > 0;
		if (eval_mode) {
			modes_buf_offset = GET_FIELD(cond_hdr->mode.data, DBG_MODE_HDR_MODES_BUF_OFFSET);
			mode_match = ecore_is_mode_match(p_hwfn, &modes_buf_offset);
		}

		if (!mode_match) {
			input_offset += cond_hdr->data_size;
			continue;
		}

		for (i = 0; i < num_entries; i++, input_offset += MEM_DUMP_ENTRY_SIZE_DWORDS) {
			const struct dbg_dump_mem *mem = (const struct dbg_dump_mem *)&input_mems_arr.ptr[input_offset];
			u8 mem_group_id = GET_FIELD(mem->dword0, DBG_DUMP_MEM_MEM_GROUP_ID);
			bool is_storm = false, mem_wide_bus;
			char storm_letter = 'a';
			u32 mem_addr, mem_len;

			if (mem_group_id >= MEM_GROUPS_NUM) {
				DP_NOTICE(p_hwfn, true, "Invalid mem_group_id\n");
				return 0;
			}

			if (!ecore_grc_is_mem_included(p_hwfn, (enum block_id)cond_hdr->block_id, mem_group_id))
				continue;

			mem_addr = GET_FIELD(mem->dword0, DBG_DUMP_MEM_ADDRESS);
			mem_len = GET_FIELD(mem->dword1, DBG_DUMP_MEM_LENGTH);
			mem_wide_bus = GET_FIELD(mem->dword1, DBG_DUMP_MEM_WIDE_BUS);

			/* Update memory length for CCFC/TCFC memories
			 * according to number of LCIDs/LTIDs.
			 */
			if (mem_group_id == MEM_GROUP_CONN_CFC_MEM) {
				if (mem_len % MAX_LCIDS) {
					DP_NOTICE(p_hwfn, true, "Invalid CCFC connection memory size\n");
					return 0;
				}

				mem_len = ecore_grc_get_param(p_hwfn, DBG_GRC_PARAM_NUM_LCIDS) * (mem_len / MAX_LCIDS);
			}
			else if (mem_group_id == MEM_GROUP_TASK_CFC_MEM) {
				if (mem_len % MAX_LTIDS) {
					DP_NOTICE(p_hwfn, true, "Invalid TCFC task memory size\n");
					return 0;
				}

				mem_len = ecore_grc_get_param(p_hwfn, DBG_GRC_PARAM_NUM_LTIDS) * (mem_len / MAX_LTIDS);
			}

			/* If memory is associated with Storm, udpate Storm
			 * details.
			 */
			if (s_block_defs[cond_hdr->block_id]->associated_to_storm) {
				is_storm = true;
				storm_letter = s_storm_defs[s_block_defs[cond_hdr->block_id]->storm_id].letter;
			}

			/* Dump memory */
			offset += ecore_grc_dump_mem(p_hwfn, p_ptt, dump_buf + offset, dump, OSAL_NULL, mem_addr, mem_len, mem_wide_bus,
				0, false, s_mem_group_names[mem_group_id], is_storm, storm_letter);
		}
	}

	return offset;
}