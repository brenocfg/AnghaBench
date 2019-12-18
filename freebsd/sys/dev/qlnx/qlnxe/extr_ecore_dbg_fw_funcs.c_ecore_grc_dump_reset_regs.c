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
typedef  size_t u32 ;
struct ecore_ptt {int dummy; } ;
struct dbg_tools_data {size_t chip_id; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/ * exists; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTES_TO_DWORDS (int /*<<< orphan*/ ) ; 
 size_t MAX_DBG_RESET_REGS ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 size_t ecore_grc_dump_reg_entry (struct ecore_hwfn*,struct ecore_ptt*,size_t*,int,int /*<<< orphan*/ ,int,int) ; 
 size_t ecore_grc_dump_regs_hdr (size_t*,int,size_t,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* s_reset_regs_defs ; 

__attribute__((used)) static u32 ecore_grc_dump_reset_regs(struct ecore_hwfn *p_hwfn,
	struct ecore_ptt *p_ptt,
	u32 *dump_buf,
	bool dump)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 i, offset = 0, num_regs = 0;

	/* Calculate header size */
	offset += ecore_grc_dump_regs_hdr(dump_buf, false, 0, "eng", -1, OSAL_NULL, OSAL_NULL);

	/* Write reset registers */
	for (i = 0; i < MAX_DBG_RESET_REGS; i++) {
		if (!s_reset_regs_defs[i].exists[dev_data->chip_id])
			continue;

		offset += ecore_grc_dump_reg_entry(p_hwfn, p_ptt, dump_buf + offset, dump, BYTES_TO_DWORDS(s_reset_regs_defs[i].addr), 1, false);
		num_regs++;
	}

	/* Write header */
	if (dump)
		ecore_grc_dump_regs_hdr(dump_buf, true, num_regs, "eng", -1, OSAL_NULL, OSAL_NULL);

	return offset;
}