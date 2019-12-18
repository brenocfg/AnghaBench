#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_15__ {TYPE_2__ data; } ;
struct TYPE_16__ {int buffer_length; TYPE_3__ u; int /*<<< orphan*/  bde_type; } ;
struct TYPE_18__ {int els_response_payload_length; int remote_id; int s_id; void* cq_id; int /*<<< orphan*/  cmd_type; void* hlm; void* sp; int /*<<< orphan*/  temporary_rpi; int /*<<< orphan*/  context_tag; int /*<<< orphan*/  ct; void* xc; void* qosd; int /*<<< orphan*/  iod; void* ox_id; void* request_tag; int /*<<< orphan*/  command; int /*<<< orphan*/  class; void* xri_tag; TYPE_4__ els_response_payload; void* xbl; void* dbde; } ;
typedef  TYPE_6__ sli4_xmit_els_rsp64_wqe_t ;
struct TYPE_13__ {scalar_t__ sgl_pre_registered; } ;
struct TYPE_19__ {TYPE_1__ config; } ;
typedef  TYPE_7__ sli4_t ;
struct TYPE_20__ {int fc_id; scalar_t__ node_group; int /*<<< orphan*/  indicator; TYPE_5__* sport; scalar_t__ attached; } ;
typedef  TYPE_8__ ocs_remote_node_t ;
struct TYPE_21__ {int /*<<< orphan*/  phys; } ;
typedef  TYPE_9__ ocs_dma_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_17__ {int /*<<< orphan*/  indicator; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CMD_GEN ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_RPI ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_VPI ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_DIR_WRITE ; 
 int SLI4_IO_CONTINUATION ; 
 int /*<<< orphan*/  SLI4_WQE_ELS_RSP64 ; 
 void* TRUE ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_xmit_els_rsp64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *rsp,
		       uint32_t rsp_len, uint16_t xri, uint16_t tag, uint16_t cq_id,
		       uint16_t ox_id, ocs_remote_node_t *rnode, uint32_t flags, uint32_t s_id)
{
	sli4_xmit_els_rsp64_wqe_t	*els = buf;

	ocs_memset(buf, 0, size);

	if (sli4->config.sgl_pre_registered) {
		els->dbde = TRUE;
	} else {
		els->xbl = TRUE;
	}

	els->els_response_payload.bde_type = SLI4_BDE_TYPE_BDE_64;
	els->els_response_payload.buffer_length = rsp_len;
	els->els_response_payload.u.data.buffer_address_low  = ocs_addr32_lo(rsp->phys);
	els->els_response_payload.u.data.buffer_address_high = ocs_addr32_hi(rsp->phys);

	els->els_response_payload_length = rsp_len;

	els->xri_tag = xri;

	els->class = SLI4_ELS_REQUEST64_CLASS_3;

	els->command = SLI4_WQE_ELS_RSP64;

	els->request_tag = tag;

	els->ox_id = ox_id;

	els->iod = SLI4_ELS_REQUEST64_DIR_WRITE;

	els->qosd = TRUE;

	if (flags & SLI4_IO_CONTINUATION) {
		els->xc = TRUE;
	}

	if (rnode->attached) {
		els->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
		els->context_tag = rnode->indicator;
	} else {
		els->ct = SLI4_ELS_REQUEST64_CONTEXT_VPI;
		els->context_tag = rnode->sport->indicator;
		els->remote_id = rnode->fc_id & 0x00ffffff;
		els->temporary_rpi = rnode->indicator;
		if (UINT32_MAX != s_id) {
			els->sp = TRUE;
			els->s_id = s_id & 0x00ffffff;
		}
	}

	if (rnode->node_group) {
		els->hlm = TRUE;
		els->remote_id = rnode->fc_id & 0x00ffffff;
	}

	els->cmd_type = SLI4_ELS_REQUEST64_CMD_GEN;

	els->cq_id = cq_id;

	return 0;
}