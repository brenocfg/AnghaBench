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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct dbg_idle_chk_info_reg {int size; int /*<<< orphan*/  data; TYPE_1__ mode; } ;
struct dbg_idle_chk_cond_reg {int entry_size; scalar_t__ start_entry; int num_entries; } ;
union dbg_idle_chk_reg {struct dbg_idle_chk_info_reg info_reg; struct dbg_idle_chk_cond_reg cond_reg; } ;
typedef  size_t u8 ;
typedef  int u32 ;
typedef  void* u16 ;
struct ecore_ptt {int dummy; } ;
struct dbg_tools_data {int /*<<< orphan*/ * block_in_reset; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_idle_chk_rule {size_t reg_offset; size_t num_cond_regs; size_t num_info_regs; int /*<<< orphan*/  severity; } ;
struct dbg_idle_chk_result_reg_hdr {size_t num_dumped_cond_regs; scalar_t__ start_entry; int size; int /*<<< orphan*/  data; int /*<<< orphan*/  num_dumped_info_regs; int /*<<< orphan*/  severity; void* mem_entry_id; void* rule_id; } ;
struct dbg_idle_chk_result_hdr {size_t num_dumped_cond_regs; scalar_t__ start_entry; int size; int /*<<< orphan*/  data; int /*<<< orphan*/  num_dumped_info_regs; int /*<<< orphan*/  severity; void* mem_entry_id; void* rule_id; } ;
struct TYPE_4__ {scalar_t__ ptr; } ;

/* Variables and functions */
 size_t BIN_BUF_DBG_IDLE_CHK_REGS ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_INFO_REG_ADDRESS ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_INFO_REG_BLOCK_ID ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_INFO_REG_WIDE_BUS ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM ; 
 int /*<<< orphan*/  DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID ; 
 int /*<<< orphan*/  DBG_MODE_HDR_EVAL_MODE ; 
 int /*<<< orphan*/  DBG_MODE_HDR_MODES_BUF_OFFSET ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 void* GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDLE_CHK_RESULT_HDR_DWORDS ; 
 int IDLE_CHK_RESULT_REG_HDR_DWORDS ; 
 int MAX_BLOCK_ID ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct dbg_idle_chk_result_reg_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ecore_grc_dump_addr_range (struct ecore_hwfn*,struct ecore_ptt*,int*,int,int,int,int) ; 
 int ecore_is_mode_match (struct ecore_hwfn*,void**) ; 
 TYPE_2__* s_dbg_arrays ; 

__attribute__((used)) static u32 ecore_idle_chk_dump_failure(struct ecore_hwfn *p_hwfn,
									   struct ecore_ptt *p_ptt,
									   u32 *dump_buf,
									   bool dump,
									   u16 rule_id,
									   const struct dbg_idle_chk_rule *rule,
									   u16 fail_entry_id,
									   u32 *cond_reg_values)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	const struct dbg_idle_chk_cond_reg *cond_regs;
	const struct dbg_idle_chk_info_reg *info_regs;
	u32 i, next_reg_offset = 0, offset = 0;
	struct dbg_idle_chk_result_hdr *hdr;
	const union dbg_idle_chk_reg *regs;
	u8 reg_id;

	hdr = (struct dbg_idle_chk_result_hdr *)dump_buf;
	regs = &((const union dbg_idle_chk_reg *)s_dbg_arrays[BIN_BUF_DBG_IDLE_CHK_REGS].ptr)[rule->reg_offset];
	cond_regs = &regs[0].cond_reg;
	info_regs = &regs[rule->num_cond_regs].info_reg;

	/* Dump rule data */
	if (dump) {
		OSAL_MEMSET(hdr, 0, sizeof(*hdr));
		hdr->rule_id = rule_id;
		hdr->mem_entry_id = fail_entry_id;
		hdr->severity = rule->severity;
		hdr->num_dumped_cond_regs = rule->num_cond_regs;
	}

	offset += IDLE_CHK_RESULT_HDR_DWORDS;

	/* Dump condition register values */
	for (reg_id = 0; reg_id < rule->num_cond_regs; reg_id++) {
		const struct dbg_idle_chk_cond_reg *reg = &cond_regs[reg_id];
		struct dbg_idle_chk_result_reg_hdr *reg_hdr;

		reg_hdr = (struct dbg_idle_chk_result_reg_hdr *)(dump_buf + offset);

		/* Write register header */
		if (!dump) {
			offset += IDLE_CHK_RESULT_REG_HDR_DWORDS + reg->entry_size;
			continue;
		}

		offset += IDLE_CHK_RESULT_REG_HDR_DWORDS;
		OSAL_MEMSET(reg_hdr, 0, sizeof(*reg_hdr));
		reg_hdr->start_entry = reg->start_entry;
		reg_hdr->size = reg->entry_size;
		SET_FIELD(reg_hdr->data, DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM, reg->num_entries > 1 || reg->start_entry > 0 ? 1 : 0);
		SET_FIELD(reg_hdr->data, DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID, reg_id);

		/* Write register values */
		for (i = 0; i < reg_hdr->size; i++, next_reg_offset++, offset++)
			dump_buf[offset] = cond_reg_values[next_reg_offset];
	}

	/* Dump info register values */
	for (reg_id = 0; reg_id < rule->num_info_regs; reg_id++) {
		const struct dbg_idle_chk_info_reg *reg = &info_regs[reg_id];
		u32 block_id;

		/* Check if register's block is in reset */
		if (!dump) {
			offset += IDLE_CHK_RESULT_REG_HDR_DWORDS + reg->size;
			continue;
		}

		block_id = GET_FIELD(reg->data, DBG_IDLE_CHK_INFO_REG_BLOCK_ID);
		if (block_id >= MAX_BLOCK_ID) {
			DP_NOTICE(p_hwfn, true, "Invalid block_id\n");
			return 0;
		}

		if (!dev_data->block_in_reset[block_id]) {
			struct dbg_idle_chk_result_reg_hdr *reg_hdr;
			bool wide_bus, eval_mode, mode_match = true;
			u16 modes_buf_offset;
			u32 addr;

			reg_hdr = (struct dbg_idle_chk_result_reg_hdr *)(dump_buf + offset);

			/* Check mode */
			eval_mode = GET_FIELD(reg->mode.data, DBG_MODE_HDR_EVAL_MODE) > 0;
			if (eval_mode) {
				modes_buf_offset = GET_FIELD(reg->mode.data, DBG_MODE_HDR_MODES_BUF_OFFSET);
				mode_match = ecore_is_mode_match(p_hwfn, &modes_buf_offset);
			}

			if (!mode_match)
				continue;

			addr = GET_FIELD(reg->data, DBG_IDLE_CHK_INFO_REG_ADDRESS);
			wide_bus = GET_FIELD(reg->data, DBG_IDLE_CHK_INFO_REG_WIDE_BUS);

			/* Write register header */
			offset += IDLE_CHK_RESULT_REG_HDR_DWORDS;
			hdr->num_dumped_info_regs++;
			OSAL_MEMSET(reg_hdr, 0, sizeof(*reg_hdr));
			reg_hdr->size = reg->size;
			SET_FIELD(reg_hdr->data, DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID, rule->num_cond_regs + reg_id);

			/* Write register values */
			offset += ecore_grc_dump_addr_range(p_hwfn, p_ptt, dump_buf + offset, dump, addr, reg->size, wide_bus);
		}
	}

	return offset;
}