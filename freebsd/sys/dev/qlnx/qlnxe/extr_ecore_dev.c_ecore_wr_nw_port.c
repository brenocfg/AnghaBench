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
typedef  int u64 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIG_REG_PMEG_IF_ADDR_BB ; 
 int /*<<< orphan*/  CNIG_REG_PMEG_IF_CMD_BB ; 
 int /*<<< orphan*/  CNIG_REG_PMEG_IF_WRDATA_BB ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ECORE_MSG_LINK ; 
 int PMEG_IF_BYTE_COUNT ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_wr_nw_port(struct ecore_hwfn	*p_hwfn,
			     struct ecore_ptt	*p_ptt,
			     u32		addr,
			     u64		data,
			     u8			reg_type,
			     u8			port)
{
	DP_VERBOSE(p_hwfn, ECORE_MSG_LINK,
		   "CMD: %08x, ADDR: 0x%08x, DATA: %08x:%08x\n",
		   ecore_rd(p_hwfn, p_ptt, CNIG_REG_PMEG_IF_CMD_BB) |
		   (8 << PMEG_IF_BYTE_COUNT),
		   (reg_type << 25) | (addr << 8) | port,
		   (u32)((data >> 32) & 0xffffffff),
		   (u32)(data & 0xffffffff));

	ecore_wr(p_hwfn, p_ptt, CNIG_REG_PMEG_IF_CMD_BB,
		 (ecore_rd(p_hwfn, p_ptt, CNIG_REG_PMEG_IF_CMD_BB) &
		  0xffff00fe) |
		 (8 << PMEG_IF_BYTE_COUNT));
	ecore_wr(p_hwfn, p_ptt, CNIG_REG_PMEG_IF_ADDR_BB,
		 (reg_type << 25) | (addr << 8) | port);
	ecore_wr(p_hwfn, p_ptt, CNIG_REG_PMEG_IF_WRDATA_BB, data & 0xffffffff);
	ecore_wr(p_hwfn, p_ptt, CNIG_REG_PMEG_IF_WRDATA_BB,
		 (data >> 32) & 0xffffffff);
}