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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int /*<<< orphan*/  BYTES_TO_DWORDS (int /*<<< orphan*/ ) ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  GRC_REG_TRACE_FIFO ; 
 int /*<<< orphan*/  GRC_REG_TRACE_FIFO_VALID_DATA ; 
 int REG_FIFO_DEPTH_DWORDS ; 
 int REG_FIFO_ELEMENT_DWORDS ; 
 int ecore_dump_common_global_params (struct ecore_hwfn*,struct ecore_ptt*,int*,int,int) ; 
 int ecore_dump_last_section (int*,int,int) ; 
 int ecore_dump_num_param (int*,int,char*,int) ; 
 int ecore_dump_section_hdr (int*,int,char*,int) ; 
 int ecore_dump_str_param (int*,int,char*,char*) ; 
 int ecore_grc_dump_addr_range (struct ecore_hwfn*,struct ecore_ptt*,int*,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dbg_status ecore_reg_fifo_dump(struct ecore_hwfn *p_hwfn,
										   struct ecore_ptt *p_ptt,
										   u32 *dump_buf,
										   bool dump,
										   u32 *num_dumped_dwords)
{
	u32 dwords_read, size_param_offset, offset = 0;
	bool fifo_has_data;

	*num_dumped_dwords = 0;

	/* Dump global params */
	offset += ecore_dump_common_global_params(p_hwfn, p_ptt, dump_buf + offset, dump, 1);
	offset += ecore_dump_str_param(dump_buf + offset, dump, "dump-type", "reg-fifo");

	/* Dump fifo data section header and param. The size param is 0 for
	 * now, and is overwritten after reading the FIFO.
	 */
	offset += ecore_dump_section_hdr(dump_buf + offset, dump, "reg_fifo_data", 1);
	size_param_offset = offset;
	offset += ecore_dump_num_param(dump_buf + offset, dump, "size", 0);

	if (dump) {
		fifo_has_data = ecore_rd(p_hwfn, p_ptt, GRC_REG_TRACE_FIFO_VALID_DATA) > 0;

		/* Pull available data from fifo. Use DMAE since this is
		 * widebus memory and must be accessed atomically. Test for
		 * dwords_read not passing buffer size since more entries could
		 * be added to the buffer as we
		 * are emptying it.
		 */
		for (dwords_read = 0; fifo_has_data && dwords_read < REG_FIFO_DEPTH_DWORDS; dwords_read += REG_FIFO_ELEMENT_DWORDS) {
			offset += ecore_grc_dump_addr_range(p_hwfn, p_ptt, dump_buf + offset, true, BYTES_TO_DWORDS(GRC_REG_TRACE_FIFO), REG_FIFO_ELEMENT_DWORDS, true);
			fifo_has_data = ecore_rd(p_hwfn, p_ptt, GRC_REG_TRACE_FIFO_VALID_DATA) > 0;
		}

		ecore_dump_num_param(dump_buf + size_param_offset, dump, "size", dwords_read);
	}
	else {

		/* FIFO max size is REG_FIFO_DEPTH_DWORDS. There is no way to
		 * test how much data is available, except for reading it.
		 */
		offset += REG_FIFO_DEPTH_DWORDS;
	}

	/* Dump last section */
	offset += ecore_dump_last_section(dump_buf, offset, dump);

	*num_dumped_dwords = offset;

	return DBG_STATUS_OK;
}