#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_15__ {TYPE_2__ data; } ;
struct TYPE_16__ {TYPE_3__ u; void* buffer_length; int /*<<< orphan*/  bde_type; } ;
struct TYPE_17__ {int remote_n_port_id; int ls; int len_loc; int cq_id; int /*<<< orphan*/  cmd_type; void* hlm; int /*<<< orphan*/  iod; void* remote_xid; void* request_tag; scalar_t__ abort_tag; void* timer; scalar_t__ pu; int /*<<< orphan*/  class; int /*<<< orphan*/  command; scalar_t__ bs; int /*<<< orphan*/  ct; scalar_t__ dif; int /*<<< orphan*/  context_tag; void* xri_tag; void* r_ctl; void* type; void* df_ctl; scalar_t__ xo; scalar_t__ ft; scalar_t__ si; scalar_t__ relative_offset; void* sequence_payload_len; TYPE_4__ bde; void* xbl; void* dbde; } ;
typedef  TYPE_5__ sli4_xmit_sequence64_wqe_t ;
struct TYPE_13__ {scalar_t__ sgl_pre_registered; } ;
struct TYPE_18__ {TYPE_1__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_6__ sli4_t ;
struct TYPE_19__ {int fc_id; scalar_t__ node_group; int /*<<< orphan*/  indicator; } ;
typedef  TYPE_7__ ocs_remote_node_t ;
struct TYPE_20__ {int /*<<< orphan*/  phys; int /*<<< orphan*/ * virt; } ;
typedef  TYPE_8__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_CMD_XMIT_SEQUENCE64_WQE ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_RPI ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_DIR_READ ; 
 int /*<<< orphan*/  SLI4_WQE_XMIT_SEQUENCE64 ; 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_xmit_sequence64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *payload,
		      uint32_t payload_len, uint8_t timeout, uint16_t ox_id,
		      uint16_t xri, uint16_t tag, ocs_remote_node_t *rnode,
		      uint8_t r_ctl, uint8_t type, uint8_t df_ctl)
{
	sli4_xmit_sequence64_wqe_t	*xmit = buf;

	ocs_memset(buf, 0, size);

	if ((payload == NULL) || (payload->virt == NULL)) {
		ocs_log_err(sli4->os, "bad parameter sgl=%p virt=%p\n",
			    payload, payload ? payload->virt : NULL);
		return -1;
	}

	if (sli4->config.sgl_pre_registered) {
		xmit->dbde = TRUE;
	} else {
		xmit->xbl = TRUE;
	}

	xmit->bde.bde_type = SLI4_BDE_TYPE_BDE_64;
	xmit->bde.buffer_length = payload_len;
	xmit->bde.u.data.buffer_address_low  = ocs_addr32_lo(payload->phys);
	xmit->bde.u.data.buffer_address_high = ocs_addr32_hi(payload->phys);
	xmit->sequence_payload_len = payload_len;

	xmit->remote_n_port_id = rnode->fc_id & 0x00ffffff;

	xmit->relative_offset = 0;

	xmit->si = 0;			/* sequence initiative - this matches what is seen from
					 * FC switches in response to FCGS commands */
	xmit->ft = 0;			/* force transmit */
	xmit->xo = 0;			/* exchange responder */
	xmit->ls = 1;			/* last in seqence */
	xmit->df_ctl = df_ctl;
	xmit->type = type;
	xmit->r_ctl = r_ctl;

	xmit->xri_tag = xri;
	xmit->context_tag = rnode->indicator;

	xmit->dif = 0;
	xmit->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
	xmit->bs = 0;

	xmit->command = SLI4_WQE_XMIT_SEQUENCE64;
	xmit->class = SLI4_ELS_REQUEST64_CLASS_3;
	xmit->pu = 0;
	xmit->timer = timeout;

	xmit->abort_tag = 0;
	xmit->request_tag = tag;
	xmit->remote_xid = ox_id;

	xmit->iod = SLI4_ELS_REQUEST64_DIR_READ;

	if (rnode->node_group) {
		xmit->hlm = TRUE;
		xmit->remote_n_port_id = rnode->fc_id & 0x00ffffff;
	}

	xmit->cmd_type = SLI4_CMD_XMIT_SEQUENCE64_WQE;

	xmit->len_loc = 2;

	xmit->cq_id = 0xFFFF;

	return 0;
}