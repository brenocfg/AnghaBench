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

/* Variables and functions */
 int BYTES_IN_DWORD ; 
 int DBG_REG_INTR_BUFFER ; 
 int DWORDS_TO_BYTES (int) ; 
 int INT_BUF_LINE_SIZE_IN_DWORDS ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int) ; 

__attribute__((used)) static u32 ecore_bus_dump_int_buf_range(struct ecore_hwfn *p_hwfn,
										struct ecore_ptt *p_ptt,
										u32 *dump_buf,
										bool dump,
										u32 start_line,
										u32 end_line)
{
	u32 line, reg_addr, i, offset = 0;

	if (!dump)
		return (end_line - start_line + 1) * INT_BUF_LINE_SIZE_IN_DWORDS;

	for (line = start_line, reg_addr = DBG_REG_INTR_BUFFER + DWORDS_TO_BYTES(start_line * INT_BUF_LINE_SIZE_IN_DWORDS);
		line <= end_line;
		line++, offset += INT_BUF_LINE_SIZE_IN_DWORDS)
		for (i = 0; i < INT_BUF_LINE_SIZE_IN_DWORDS; i++, reg_addr += BYTES_IN_DWORD)
			dump_buf[offset + INT_BUF_LINE_SIZE_IN_DWORDS - 1 - i] = ecore_rd(p_hwfn, p_ptt, reg_addr);

	return offset;
}