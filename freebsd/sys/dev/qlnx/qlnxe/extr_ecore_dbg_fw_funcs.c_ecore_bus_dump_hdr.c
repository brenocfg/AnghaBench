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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {int hw_dwords; size_t target; scalar_t__ one_shot_en; int /*<<< orphan*/  hw_id_mask; } ;
struct dbg_tools_data {TYPE_1__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  int /*<<< orphan*/  hw_id_mask_str ;

/* Variables and functions */
 size_t DBG_BUS_TARGET_ID_NIG ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 scalar_t__ OSAL_SNPRINTF (char*,int,char*,int /*<<< orphan*/ ) ; 
 int ecore_bus_dump_data (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 
 int ecore_bus_dump_inputs (struct ecore_hwfn*,int*,int) ; 
 int ecore_dump_common_global_params (struct ecore_hwfn*,struct ecore_ptt*,int*,int,int) ; 
 int ecore_dump_num_param (int*,int,char*,int) ; 
 int ecore_dump_section_hdr (int*,int,char*,int) ; 
 int ecore_dump_str_param (int*,int,char*,char*) ; 
 char** s_dbg_target_names ; 

__attribute__((used)) static u32 ecore_bus_dump_hdr(struct ecore_hwfn *p_hwfn,
							  struct ecore_ptt *p_ptt,
							  u32 *dump_buf,
							  bool dump)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	char hw_id_mask_str[16];
	u32 offset = 0;

	if (OSAL_SNPRINTF(hw_id_mask_str, sizeof(hw_id_mask_str), "0x%x", dev_data->bus.hw_id_mask) < 0)
		DP_NOTICE(p_hwfn, true, "Unexpected debug error: invalid HW ID mask\n");

	/* Dump global params */
	offset += ecore_dump_common_global_params(p_hwfn, p_ptt, dump_buf + offset, dump, 5);
	offset += ecore_dump_str_param(dump_buf + offset, dump, "dump-type", "debug-bus");
	offset += ecore_dump_str_param(dump_buf + offset, dump, "wrap-mode", dev_data->bus.one_shot_en ? "one-shot" : "wrap-around");
	offset += ecore_dump_num_param(dump_buf + offset, dump, "hw-dwords", dev_data->bus.hw_dwords);
	offset += ecore_dump_str_param(dump_buf + offset, dump, "hw-id-mask", hw_id_mask_str);
	offset += ecore_dump_str_param(dump_buf + offset, dump, "target", s_dbg_target_names[dev_data->bus.target]);

	offset += ecore_bus_dump_inputs(p_hwfn, dump_buf + offset, dump);

	if (dev_data->bus.target != DBG_BUS_TARGET_ID_NIG) {
		u32 recorded_dwords = 0;
		
		if (dump)
			recorded_dwords = ecore_bus_dump_data(p_hwfn, p_ptt, OSAL_NULL, false);

		offset += ecore_dump_section_hdr(dump_buf + offset, dump, "bus_data", 1);
		offset += ecore_dump_num_param(dump_buf + offset, dump, "size", recorded_dwords);
	}

	return offset;
}