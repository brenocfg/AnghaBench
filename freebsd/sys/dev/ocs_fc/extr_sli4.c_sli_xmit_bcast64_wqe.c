#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_13__ {TYPE_1__ data; } ;
struct TYPE_14__ {TYPE_2__ u; void* buffer_length; int /*<<< orphan*/  bde_type; } ;
struct TYPE_16__ {int len_loc; void* cq_id; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  iod; int /*<<< orphan*/  temporary_rpi; void* request_tag; void* timer; int /*<<< orphan*/  command; int /*<<< orphan*/  class; int /*<<< orphan*/  context_tag; int /*<<< orphan*/  ct; void* xri_tag; void* r_ctl; void* type; void* df_ctl; void* sequence_payload_length; TYPE_3__ sequence_payload; int /*<<< orphan*/  dbde; } ;
typedef  TYPE_5__ sli4_xmit_bcast64_wqe_t ;
struct TYPE_17__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_6__ sli4_t ;
struct TYPE_18__ {int /*<<< orphan*/  indicator; TYPE_4__* sport; scalar_t__ attached; } ;
typedef  TYPE_7__ ocs_remote_node_t ;
struct TYPE_19__ {int /*<<< orphan*/  phys; } ;
typedef  TYPE_8__ ocs_dma_t ;
typedef  int int32_t ;
struct TYPE_15__ {int /*<<< orphan*/  indicator; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_CMD_XMIT_BCAST64_WQE ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_VPI ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_DIR_WRITE ; 
 int /*<<< orphan*/  SLI4_WQE_XMIT_BCAST64 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_xmit_bcast64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *payload,
		uint32_t payload_len, uint8_t timeout, uint16_t xri, uint16_t tag,
		uint16_t cq_id, ocs_remote_node_t *rnode,
		uint8_t r_ctl, uint8_t type, uint8_t df_ctl)
{
	sli4_xmit_bcast64_wqe_t *bcast = buf;

	/* Command requires a temporary RPI (i.e. unused remote node) */
	if (rnode->attached) {
		ocs_log_test(sli4->os, "remote node %d in use\n", rnode->indicator);
		return -1;
	}

	ocs_memset(buf, 0, size);

	bcast->dbde = TRUE;
	bcast->sequence_payload.bde_type = SLI4_BDE_TYPE_BDE_64;
	bcast->sequence_payload.buffer_length = payload_len;
	bcast->sequence_payload.u.data.buffer_address_low  = ocs_addr32_lo(payload->phys);
	bcast->sequence_payload.u.data.buffer_address_high = ocs_addr32_hi(payload->phys);

	bcast->sequence_payload_length = payload_len;

	bcast->df_ctl = df_ctl;
	bcast->type = type;
	bcast->r_ctl = r_ctl;

	bcast->xri_tag = xri;

	bcast->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
	bcast->context_tag = rnode->sport->indicator;

	bcast->class = SLI4_ELS_REQUEST64_CLASS_3;

	bcast->command = SLI4_WQE_XMIT_BCAST64;

	bcast->timer = timeout;

	bcast->request_tag = tag;

	bcast->temporary_rpi = rnode->indicator;

	bcast->len_loc = 0x1;

	bcast->iod = SLI4_ELS_REQUEST64_DIR_WRITE;

	bcast->cmd_type = SLI4_CMD_XMIT_BCAST64_WQE;

	bcast->cq_id = cq_id;

	return 0;
}