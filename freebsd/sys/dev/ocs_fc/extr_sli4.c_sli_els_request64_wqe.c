#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_19__ {scalar_t__ sgl_pre_registered; } ;
struct TYPE_26__ {int /*<<< orphan*/  os; int /*<<< orphan*/  if_type; TYPE_1__ config; } ;
typedef  TYPE_8__ sli4_t ;
struct TYPE_27__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
typedef  TYPE_9__ sli4_sge_t ;
struct TYPE_21__ {int /*<<< orphan*/  sgl_segment_address_high; int /*<<< orphan*/  sgl_segment_address_low; } ;
struct TYPE_20__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_22__ {TYPE_3__ blp; TYPE_2__ data; } ;
struct TYPE_23__ {int buffer_length; TYPE_4__ u; int /*<<< orphan*/  bde_type; } ;
struct TYPE_16__ {int timer; int remote_id; scalar_t__ ct; int /*<<< orphan*/  temporary_rpi; void* cq_id; int /*<<< orphan*/  cmd_type; int /*<<< orphan*/  context_tag; void* els_id; int /*<<< orphan*/  sid; void* sp; void* qosd; int /*<<< orphan*/  iod; void* hlm; void* request_tag; int /*<<< orphan*/  command; int /*<<< orphan*/  class; void* xri_tag; void* max_response_payload_length; void* els_request_payload_length; TYPE_5__ els_request_payload; void* xbl; void* dbde; } ;
typedef  TYPE_10__ sli4_els_request64_wqe_t ;
struct TYPE_17__ {int fc_id; int /*<<< orphan*/  indicator; TYPE_7__* sport; int /*<<< orphan*/  attached; scalar_t__ node_group; } ;
typedef  TYPE_11__ ocs_remote_node_t ;
struct TYPE_18__ {int /*<<< orphan*/  phys; TYPE_9__* virt; } ;
typedef  TYPE_12__ ocs_dma_t ;
typedef  int int32_t ;
struct TYPE_25__ {int /*<<< orphan*/  indicator; int /*<<< orphan*/  fc_id; TYPE_6__* domain; } ;
struct TYPE_24__ {int /*<<< orphan*/  fcf_indicator; } ;

/* Variables and functions */
 void* FALSE ; 
 int FC_ADDR_FABRIC ; 
#define  FC_ELS_CMD_FDISC 132 
#define  FC_ELS_CMD_FLOGI 131 
#define  FC_ELS_CMD_LOGO 130 
#define  FC_ELS_CMD_PLOGI 129 
#define  FC_ELS_CMD_SCR 128 
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_BDE_TYPE_BLP ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CMD_FABRIC ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CMD_NON_FABRIC ; 
 scalar_t__ SLI4_ELS_REQUEST64_CONTEXT_FCFI ; 
 scalar_t__ SLI4_ELS_REQUEST64_CONTEXT_RPI ; 
 scalar_t__ SLI4_ELS_REQUEST64_CONTEXT_VPI ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_DIR_READ ; 
 void* SLI4_ELS_REQUEST64_FDISC ; 
 void* SLI4_ELS_REQUEST64_FLOGIN ; 
 void* SLI4_ELS_REQUEST64_LOGO ; 
 void* SLI4_ELS_REQUEST64_OTHER ; 
 void* SLI4_ELS_REQUEST64_PLOGI ; 
 int /*<<< orphan*/  SLI4_IF_TYPE_BE3_SKH_PF ; 
 int /*<<< orphan*/  SLI4_WQE_ELS_REQUEST64 ; 
 void* TRUE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_els_request64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *sgl, uint8_t req_type,
		      uint32_t req_len, uint32_t max_rsp_len, uint8_t timeout,
		      uint16_t xri, uint16_t tag, uint16_t cq_id, ocs_remote_node_t *rnode)
{
	sli4_els_request64_wqe_t	*els = buf;
	sli4_sge_t	*sge = sgl->virt;
	uint8_t		is_fabric = FALSE;

	ocs_memset(buf, 0, size);

	if (sli4->config.sgl_pre_registered) {
		els->xbl = FALSE;

		els->dbde = TRUE;
		els->els_request_payload.bde_type = SLI4_BDE_TYPE_BDE_64;

		els->els_request_payload.buffer_length = req_len;
		els->els_request_payload.u.data.buffer_address_low  = sge[0].buffer_address_low;
		els->els_request_payload.u.data.buffer_address_high = sge[0].buffer_address_high;
	} else {
		els->xbl = TRUE;

		els->els_request_payload.bde_type = SLI4_BDE_TYPE_BLP;

		els->els_request_payload.buffer_length = 2 * sizeof(sli4_sge_t);
		els->els_request_payload.u.blp.sgl_segment_address_low  = ocs_addr32_lo(sgl->phys);
		els->els_request_payload.u.blp.sgl_segment_address_high = ocs_addr32_hi(sgl->phys);
	}

	els->els_request_payload_length = req_len;
	els->max_response_payload_length = max_rsp_len;

	els->xri_tag = xri;
	els->timer = timeout;
	els->class = SLI4_ELS_REQUEST64_CLASS_3;

	els->command = SLI4_WQE_ELS_REQUEST64;

	els->request_tag = tag;

	if (rnode->node_group) {
		els->hlm = TRUE;
		els->remote_id = rnode->fc_id & 0x00ffffff;
	}

	els->iod = SLI4_ELS_REQUEST64_DIR_READ;

	els->qosd = TRUE;

	/* figure out the ELS_ID value from the request buffer */

	switch (req_type) {
	case FC_ELS_CMD_LOGO:
		els->els_id = SLI4_ELS_REQUEST64_LOGO;
		if (rnode->attached) {
			els->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
			els->context_tag = rnode->indicator;
		} else {
			els->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
			els->context_tag = rnode->sport->indicator;
		}
		if (FC_ADDR_FABRIC == rnode->fc_id) {
			is_fabric = TRUE;
		}
		break;
	case FC_ELS_CMD_FDISC:
		if (FC_ADDR_FABRIC == rnode->fc_id) {
			is_fabric = TRUE;
		}
		if (0 == rnode->sport->fc_id) {
			els->els_id = SLI4_ELS_REQUEST64_FDISC;
			is_fabric = TRUE;
		} else {
			els->els_id = SLI4_ELS_REQUEST64_OTHER;
		}
		els->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
		els->context_tag = rnode->sport->indicator;
		els->sp = TRUE;
		break;
	case FC_ELS_CMD_FLOGI:
		els->els_id = SLI4_ELS_REQUEST64_FLOGIN;
		is_fabric = TRUE;
		if (SLI4_IF_TYPE_BE3_SKH_PF == sli4->if_type) {
			if (!rnode->sport->domain) {
				ocs_log_test(sli4->os, "invalid domain handle\n");
				return -1;
			}
			/*
			 * IF_TYPE 0 skips INIT_VFI/INIT_VPI and therefore must use the
			 * FCFI here
			 */
			els->ct = SLI4_ELS_REQUEST64_CONTEXT_FCFI;
			els->context_tag = rnode->sport->domain->fcf_indicator;
			els->sp = TRUE;
		} else {
			els->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
			els->context_tag = rnode->sport->indicator;

			/*
			 * Set SP here ... we haven't done a REG_VPI yet
			 * TODO: need to maybe not set this when we have
			 *       completed VFI/VPI registrations ...
			 *
			 * Use the FC_ID of the SPORT if it has been allocated, otherwise
			 * use an S_ID of zero.
			 */
			els->sp = TRUE;
			if (rnode->sport->fc_id != UINT32_MAX) {
				els->sid = rnode->sport->fc_id;
			}
		}
		break;
	case FC_ELS_CMD_PLOGI:
		els->els_id = SLI4_ELS_REQUEST64_PLOGI;
		els->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
		els->context_tag = rnode->sport->indicator;
		break;
	case FC_ELS_CMD_SCR:
		els->els_id = SLI4_ELS_REQUEST64_OTHER;
		els->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
		els->context_tag = rnode->sport->indicator;
		break;
	default:
		els->els_id = SLI4_ELS_REQUEST64_OTHER;
		if (rnode->attached) {
			els->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
			els->context_tag = rnode->indicator;
		} else {
			els->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
			els->context_tag = rnode->sport->indicator;
		}
		break;
	}

	if (is_fabric) {
		els->cmd_type = SLI4_ELS_REQUEST64_CMD_FABRIC;
	} else {
		els->cmd_type = SLI4_ELS_REQUEST64_CMD_NON_FABRIC;
	}

	els->cq_id = cq_id;

	if (SLI4_ELS_REQUEST64_CONTEXT_RPI != els->ct) {
		els->remote_id = rnode->fc_id;
	}
	if (SLI4_ELS_REQUEST64_CONTEXT_VPI == els->ct) {
		els->temporary_rpi = rnode->indicator;
	}

	return 0;
}