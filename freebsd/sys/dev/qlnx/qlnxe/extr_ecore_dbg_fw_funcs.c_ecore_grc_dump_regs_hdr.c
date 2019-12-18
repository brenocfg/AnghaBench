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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int ecore_dump_num_param (int*,int,char*,int) ; 
 int ecore_dump_section_hdr (int*,int,char*,int) ; 
 int ecore_dump_str_param (int*,int,char const*,char const*) ; 

__attribute__((used)) static u32 ecore_grc_dump_regs_hdr(u32 *dump_buf,
								   bool dump,
								   u32 num_reg_entries,
								   const char *split_type,
								   int split_id,
								   const char *param_name,
								   const char *param_val)
{
	u8 num_params = 2 + (split_id >= 0 ? 1 : 0) + (param_name ? 1 : 0);
	u32 offset = 0;

	offset += ecore_dump_section_hdr(dump_buf + offset, dump, "grc_regs", num_params);
	offset += ecore_dump_num_param(dump_buf + offset, dump, "count", num_reg_entries);
	offset += ecore_dump_str_param(dump_buf + offset, dump, "split", split_type);
	if (split_id >= 0)
		offset += ecore_dump_num_param(dump_buf + offset, dump, "id", split_id);
	if (param_name && param_val)
		offset += ecore_dump_str_param(dump_buf + offset, dump, param_name, param_val);

	return offset;
}