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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct dbg_tools_data {size_t chip_id; size_t platform_id; } ;
struct ecore_hwfn {int /*<<< orphan*/  abs_pf_id; struct dbg_tools_data dbg_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ NUM_COMMON_GLOBAL_PARAMS ; 
 int /*<<< orphan*/  TOOLS_VERSION ; 
 int ecore_dump_fw_ver_param (struct ecore_hwfn*,struct ecore_ptt*,int*,int) ; 
 int ecore_dump_mfw_ver_param (struct ecore_hwfn*,struct ecore_ptt*,int*,int) ; 
 int ecore_dump_num_param (int*,int,char*,int /*<<< orphan*/ ) ; 
 int ecore_dump_section_hdr (int*,int,char*,scalar_t__) ; 
 int ecore_dump_str_param (int*,int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* s_chip_defs ; 
 TYPE_1__* s_platform_defs ; 

__attribute__((used)) static u32 ecore_dump_common_global_params(struct ecore_hwfn *p_hwfn,
										   struct ecore_ptt *p_ptt,
										   u32 *dump_buf,
										   bool dump,
										   u8 num_specific_global_params)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 offset = 0;
	u8 num_params;

	/* Dump global params section header */
	num_params = NUM_COMMON_GLOBAL_PARAMS + num_specific_global_params;
	offset += ecore_dump_section_hdr(dump_buf + offset, dump, "global_params", num_params);

	/* Store params */
	offset += ecore_dump_fw_ver_param(p_hwfn, p_ptt, dump_buf + offset, dump);
	offset += ecore_dump_mfw_ver_param(p_hwfn, p_ptt, dump_buf + offset, dump);
	offset += ecore_dump_num_param(dump_buf + offset, dump, "tools-version", TOOLS_VERSION);
	offset += ecore_dump_str_param(dump_buf + offset, dump, "chip", s_chip_defs[dev_data->chip_id].name);
	offset += ecore_dump_str_param(dump_buf + offset, dump, "platform", s_platform_defs[dev_data->platform_id].name);
	offset += ecore_dump_num_param(dump_buf + offset, dump, "pci-func", p_hwfn->abs_pf_id);

	return offset;
}