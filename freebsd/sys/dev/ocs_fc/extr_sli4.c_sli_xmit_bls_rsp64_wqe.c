#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct TYPE_11__ {int seq_id_last; int seq_id_validity; int /*<<< orphan*/  low_seq_cnt; int /*<<< orphan*/  high_seq_cnt; } ;
struct TYPE_12__ {int /*<<< orphan*/  rjt; TYPE_1__ acc; } ;
struct TYPE_14__ {scalar_t__ type; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; TYPE_2__ u; } ;
typedef  TYPE_4__ sli_bls_payload_t ;
struct TYPE_15__ {int payload_word0; scalar_t__ context_tag; int local_n_port_id; int remote_id; scalar_t__ temporary_rpi; int /*<<< orphan*/  cmd_type; void* cq_id; void* hlm; void* qosd; void* request_tag; int /*<<< orphan*/  command; int /*<<< orphan*/  class; void* xri_tag; int /*<<< orphan*/  ct; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; void* ar; int /*<<< orphan*/  low_seq_cnt; int /*<<< orphan*/  high_seq_cnt; } ;
typedef  TYPE_5__ sli4_xmit_bls_rsp_wqe_t ;
struct TYPE_16__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_6__ sli4_t ;
struct TYPE_17__ {scalar_t__ indicator; int fc_id; scalar_t__ node_group; TYPE_3__* sport; scalar_t__ attached; } ;
typedef  TYPE_7__ ocs_remote_node_t ;
typedef  int int32_t ;
struct TYPE_13__ {scalar_t__ indicator; int fc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_CMD_XMIT_BLS_RSP64_WQE ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_RPI ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_VPI ; 
 int /*<<< orphan*/  SLI4_WQE_XMIT_BLS_RSP ; 
 scalar_t__ SLI_BLS_ACC ; 
 scalar_t__ SLI_BLS_RJT ; 
 void* TRUE ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_xmit_bls_rsp64_wqe(sli4_t *sli4, void *buf, size_t size, sli_bls_payload_t *payload,
		       uint16_t xri, uint16_t tag, uint16_t cq_id, ocs_remote_node_t *rnode, uint32_t s_id)
{
	sli4_xmit_bls_rsp_wqe_t *bls = buf;

	/*
	 * Callers can either specify RPI or S_ID, but not both
	 */
	if (rnode->attached && (s_id != UINT32_MAX)) {
		ocs_log_test(sli4->os, "S_ID specified for attached remote node %d\n",
			     rnode->indicator);
		return -1;
	}

	ocs_memset(buf, 0, size);

	if (SLI_BLS_ACC == payload->type) {
		bls->payload_word0 = (payload->u.acc.seq_id_last << 16) |
			(payload->u.acc.seq_id_validity << 24);
		bls->high_seq_cnt = payload->u.acc.high_seq_cnt;
		bls->low_seq_cnt = payload->u.acc.low_seq_cnt;
	} else if (SLI_BLS_RJT == payload->type) {
		bls->payload_word0 = *((uint32_t *)&payload->u.rjt);
		bls->ar = TRUE;
	} else {
		ocs_log_test(sli4->os, "bad BLS type %#x\n",
				payload->type);
		return -1;
	}

	bls->ox_id = payload->ox_id;
	bls->rx_id = payload->rx_id;

	if (rnode->attached) {
		bls->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
		bls->context_tag = rnode->indicator;
	} else {
		bls->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
		bls->context_tag = rnode->sport->indicator;

		if (UINT32_MAX != s_id) {
			bls->local_n_port_id = s_id & 0x00ffffff;
		} else {
			bls->local_n_port_id = rnode->sport->fc_id & 0x00ffffff;
		}
		bls->remote_id = rnode->fc_id & 0x00ffffff;

		bls->temporary_rpi = rnode->indicator;
	}

	bls->xri_tag = xri;

	bls->class = SLI4_ELS_REQUEST64_CLASS_3;

	bls->command = SLI4_WQE_XMIT_BLS_RSP;

	bls->request_tag = tag;

	bls->qosd = TRUE;

	if (rnode->node_group) {
		bls->hlm = TRUE;
		bls->remote_id = rnode->fc_id & 0x00ffffff;
	}

	bls->cq_id = cq_id;

	bls->cmd_type = SLI4_CMD_XMIT_BLS_RSP64_WQE;

	return 0;
}