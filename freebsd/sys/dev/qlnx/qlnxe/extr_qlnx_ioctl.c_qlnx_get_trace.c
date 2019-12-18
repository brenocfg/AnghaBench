#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_8__ {int* size; int cmd; int* dwords; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ qlnx_trace_t ;
struct TYPE_7__ {struct ecore_hwfn* hwfns; } ;
struct TYPE_9__ {TYPE_1__ cdev; } ;
typedef  TYPE_3__ qlnx_host_t ;

/* Variables and functions */
 int DBG_STATUS_OK ; 
 int ENXIO ; 
#define  QLNX_FW_ASSERTS 132 
#define  QLNX_IGU_FIFO 131 
#define  QLNX_MCP_TRACE 130 
#define  QLNX_PROTECTION_OVERRIDE 129 
#define  QLNX_REG_FIFO 128 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_3__*,char*,int,int) ; 
 int copyout (void*,int /*<<< orphan*/ ,int) ; 
 int ecore_dbg_fw_asserts_dump (struct ecore_hwfn*,struct ecore_ptt*,void*,int,int*) ; 
 int /*<<< orphan*/  ecore_dbg_get_fw_func_ver () ; 
 int ecore_dbg_igu_fifo_dump (struct ecore_hwfn*,struct ecore_ptt*,void*,int,int*) ; 
 int ecore_dbg_mcp_trace_dump (struct ecore_hwfn*,struct ecore_ptt*,void*,int,int*) ; 
 int ecore_dbg_protection_override_dump (struct ecore_hwfn*,struct ecore_ptt*,void*,int,int*) ; 
 int ecore_dbg_reg_fifo_dump (struct ecore_hwfn*,struct ecore_ptt*,void*,int,int*) ; 
 int /*<<< orphan*/  ecore_dbg_set_app_ver (int /*<<< orphan*/ ) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 
 void* qlnx_zalloc (int) ; 

__attribute__((used)) static int
qlnx_get_trace(qlnx_host_t *ha, int hwfn_index, qlnx_trace_t *trace)
{
        int rval = -1;
        struct ecore_hwfn *p_hwfn;
        struct ecore_ptt *p_ptt;
	uint32_t num_dwords = 0;
	void *buffer;

	buffer = qlnx_zalloc(trace->size[hwfn_index]);
	if (buffer == NULL) { 
                QL_DPRINT1(ha,"qlnx_zalloc [%d, 0x%x]failed\n",
                           hwfn_index, trace->cmd);
                return (ENXIO);
	}
	ecore_dbg_set_app_ver(ecore_dbg_get_fw_func_ver());

        p_hwfn = &ha->cdev.hwfns[hwfn_index];
        p_ptt = ecore_ptt_acquire(p_hwfn);

        if (!p_ptt) {
                QL_DPRINT1(ha, "ecore_ptt_acquire [%d, 0x%x]failed\n",
                           hwfn_index, trace->cmd);
                return (ENXIO);
        }

	switch (trace->cmd) {

	case QLNX_MCP_TRACE:
        	rval = ecore_dbg_mcp_trace_dump(p_hwfn, p_ptt,
				buffer, (trace->size[hwfn_index] >> 2),
				&num_dwords);
		break;

	case QLNX_REG_FIFO:
        	rval = ecore_dbg_reg_fifo_dump(p_hwfn, p_ptt,
				buffer, (trace->size[hwfn_index] >> 2),
				&num_dwords);
		break;

	case QLNX_IGU_FIFO:
        	rval = ecore_dbg_igu_fifo_dump(p_hwfn, p_ptt,
				buffer, (trace->size[hwfn_index] >> 2),
				&num_dwords);
		break;

	case QLNX_PROTECTION_OVERRIDE:
        	rval = ecore_dbg_protection_override_dump(p_hwfn, p_ptt,
				buffer, (trace->size[hwfn_index] >> 2),
				&num_dwords);
		break;

	case QLNX_FW_ASSERTS:
        	rval = ecore_dbg_fw_asserts_dump(p_hwfn, p_ptt,
				buffer, (trace->size[hwfn_index] >> 2),
				&num_dwords);
		break;
	}

        if (rval != DBG_STATUS_OK) {
                QL_DPRINT1(ha,"cmd = 0x%x failed [0x%x]\n", trace->cmd, rval);
		num_dwords = 0;
        }

        ecore_ptt_release(p_hwfn, p_ptt);

	trace->dwords[hwfn_index] = num_dwords;

	if (num_dwords) {
               	rval = copyout(buffer, trace->buffer[hwfn_index],
				(num_dwords << 2));
	}

        return (rval);
}