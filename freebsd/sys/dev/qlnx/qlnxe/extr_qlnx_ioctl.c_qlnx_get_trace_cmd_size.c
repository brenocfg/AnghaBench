#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_5__ {struct ecore_hwfn* hwfns; } ;
struct TYPE_6__ {TYPE_1__ cdev; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int DBG_STATUS_OK ; 
#define  QLNX_FW_ASSERTS 132 
#define  QLNX_IGU_FIFO 131 
#define  QLNX_MCP_TRACE 130 
#define  QLNX_PROTECTION_OVERRIDE 129 
#define  QLNX_REG_FIFO 128 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,char*,int,int) ; 
 int ecore_dbg_fw_asserts_get_dump_buf_size (struct ecore_hwfn*,struct ecore_ptt*,int*) ; 
 int ecore_dbg_igu_fifo_get_dump_buf_size (struct ecore_hwfn*,struct ecore_ptt*,int*) ; 
 int ecore_dbg_mcp_trace_get_dump_buf_size (struct ecore_hwfn*,struct ecore_ptt*,int*) ; 
 int ecore_dbg_protection_override_get_dump_buf_size (struct ecore_hwfn*,struct ecore_ptt*,int*) ; 
 int ecore_dbg_reg_fifo_get_dump_buf_size (struct ecore_hwfn*,struct ecore_ptt*,int*) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

__attribute__((used)) static uint32_t
qlnx_get_trace_cmd_size(qlnx_host_t *ha, int hwfn_index, uint16_t cmd)
{
        int rval = -1;
        struct ecore_hwfn *p_hwfn;
        struct ecore_ptt *p_ptt;
	uint32_t num_dwords = 0;

        p_hwfn = &ha->cdev.hwfns[hwfn_index];
        p_ptt = ecore_ptt_acquire(p_hwfn);

        if (!p_ptt) {
                QL_DPRINT1(ha, "ecore_ptt_acquire [%d, 0x%x]failed\n",
                           hwfn_index, cmd);
                return (0);
        }

	switch (cmd) {

	case QLNX_MCP_TRACE:
        	rval = ecore_dbg_mcp_trace_get_dump_buf_size(p_hwfn,
				p_ptt, &num_dwords);
		break;

	case QLNX_REG_FIFO:
        	rval = ecore_dbg_reg_fifo_get_dump_buf_size(p_hwfn,
				p_ptt, &num_dwords);
		break;

	case QLNX_IGU_FIFO:
        	rval = ecore_dbg_igu_fifo_get_dump_buf_size(p_hwfn,
				p_ptt, &num_dwords);
		break;

	case QLNX_PROTECTION_OVERRIDE:
        	rval = ecore_dbg_protection_override_get_dump_buf_size(p_hwfn,
				p_ptt, &num_dwords);
		break;

	case QLNX_FW_ASSERTS:
        	rval = ecore_dbg_fw_asserts_get_dump_buf_size(p_hwfn,
				p_ptt, &num_dwords);
		break;
	}

        if (rval != DBG_STATUS_OK) {
                QL_DPRINT1(ha,"cmd = 0x%x failed [0x%x]\n", cmd, rval);
		num_dwords = 0;
        }

        ecore_ptt_release(p_hwfn, p_ptt);

        return ((num_dwords * sizeof (uint32_t)));
}