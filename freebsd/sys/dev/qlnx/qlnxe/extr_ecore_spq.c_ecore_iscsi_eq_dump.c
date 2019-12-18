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
struct TYPE_3__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  icid; } ;
struct TYPE_4__ {TYPE_1__ iscsi_info; } ;
struct event_ring_entry {int opcode; TYPE_2__ data; int /*<<< orphan*/  fw_return_code; int /*<<< orphan*/  echo; } ;
struct ecore_hwfn {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_STORAGE ; 
#define  ISCSI_EVENT_TYPE_ASYN_ABORT_RCVD 144 
#define  ISCSI_EVENT_TYPE_ASYN_CLOSE_RCVD 143 
#define  ISCSI_EVENT_TYPE_ASYN_CONNECT_COMPLETE 142 
#define  ISCSI_EVENT_TYPE_ASYN_FIN_WAIT2 141 
#define  ISCSI_EVENT_TYPE_ASYN_MAX_KA_PROBES_CNT 140 
#define  ISCSI_EVENT_TYPE_ASYN_MAX_RT_CNT 139 
#define  ISCSI_EVENT_TYPE_ASYN_MAX_RT_TIME 138 
#define  ISCSI_EVENT_TYPE_ASYN_SYN_RCVD 137 
#define  ISCSI_EVENT_TYPE_ASYN_TERMINATE_DONE 136 
#define  ISCSI_EVENT_TYPE_CLEAR_SQ 135 
#define  ISCSI_EVENT_TYPE_DESTROY_FUNC 134 
#define  ISCSI_EVENT_TYPE_INIT_FUNC 133 
#define  ISCSI_EVENT_TYPE_ISCSI_CONN_ERROR 132 
#define  ISCSI_EVENT_TYPE_OFFLOAD_CONN 131 
#define  ISCSI_EVENT_TYPE_TCP_CONN_ERROR 130 
#define  ISCSI_EVENT_TYPE_TERMINATE_CONN 129 
#define  ISCSI_EVENT_TYPE_UPDATE_CONN 128 
 int MAX_ISCSI_EQE_OPCODE ; 
 int /*<<< orphan*/  OSAL_LE16_TO_CPU (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_iscsi_eq_dump(struct ecore_hwfn *p_hwfn,
				struct event_ring_entry *p_eqe)
{
	if (p_eqe->opcode >= MAX_ISCSI_EQE_OPCODE) {
		DP_NOTICE(p_hwfn, false, "Unknown iSCSI EQ: %x\n",
			  p_eqe->opcode);
	}

	switch (p_eqe->opcode) {
	case ISCSI_EVENT_TYPE_INIT_FUNC:
	case ISCSI_EVENT_TYPE_DESTROY_FUNC:
		/* NOPE */
		break;
	case ISCSI_EVENT_TYPE_OFFLOAD_CONN:
	case ISCSI_EVENT_TYPE_TERMINATE_CONN:
		DP_VERBOSE(p_hwfn, ECORE_MSG_STORAGE,
			   "iSCSI EQE: Port %x, Op %x, echo %x, FWret %x, CID %x, ConnID %x, ERR %x\n",
			   p_hwfn->port_id, p_eqe->opcode,
			   OSAL_LE16_TO_CPU(p_eqe->echo),
			   p_eqe->fw_return_code,
			   OSAL_LE16_TO_CPU(p_eqe->data.iscsi_info.icid),
			   OSAL_LE16_TO_CPU(p_eqe->data.iscsi_info.conn_id),
			   p_eqe->data.iscsi_info.error_code);
		break;
	case ISCSI_EVENT_TYPE_UPDATE_CONN:
	case ISCSI_EVENT_TYPE_CLEAR_SQ:
	case ISCSI_EVENT_TYPE_ASYN_CONNECT_COMPLETE:
	case ISCSI_EVENT_TYPE_ASYN_TERMINATE_DONE:
	case ISCSI_EVENT_TYPE_ASYN_ABORT_RCVD:
	case ISCSI_EVENT_TYPE_ASYN_CLOSE_RCVD:
	case ISCSI_EVENT_TYPE_ASYN_SYN_RCVD:
	case ISCSI_EVENT_TYPE_ASYN_MAX_RT_TIME:
	case ISCSI_EVENT_TYPE_ASYN_MAX_RT_CNT:
	case ISCSI_EVENT_TYPE_ASYN_MAX_KA_PROBES_CNT:
	case ISCSI_EVENT_TYPE_ASYN_FIN_WAIT2:
	case ISCSI_EVENT_TYPE_ISCSI_CONN_ERROR:
	case ISCSI_EVENT_TYPE_TCP_CONN_ERROR:
	default:
		/* NOPE */
		break;
	}
}