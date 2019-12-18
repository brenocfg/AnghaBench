#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  size_t uint32_t ;
typedef  void* uint16_t ;
struct TYPE_29__ {scalar_t__ perf_hint; scalar_t__ sgl_pre_registered; } ;
struct TYPE_33__ {TYPE_5__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_9__ sli4_t ;
struct TYPE_20__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; scalar_t__ buffer_length; int /*<<< orphan*/  sge_type; } ;
typedef  TYPE_10__ sli4_sge_t ;
struct TYPE_30__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_31__ {TYPE_6__ data; } ;
struct TYPE_32__ {TYPE_7__ u; scalar_t__ buffer_length; void* bde_type; } ;
struct TYPE_26__ {int /*<<< orphan*/  sgl_segment_address_high; int /*<<< orphan*/  sgl_segment_address_low; } ;
struct TYPE_25__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_27__ {TYPE_2__ blp; TYPE_1__ data; } ;
struct TYPE_28__ {TYPE_3__ u; scalar_t__ buffer_length; void* bde_type; } ;
struct TYPE_21__ {size_t total_transfer_length; size_t context_tag; int pu; int len_loc; int remote_n_port_id; TYPE_8__ first_data_bde; void* cq_id; int /*<<< orphan*/  cmd_type; void* erp; void* hlm; void* request_tag; void* abort_tag; void* bs; void* dif; int /*<<< orphan*/  ct; int /*<<< orphan*/  command; int /*<<< orphan*/  class; void* timer; void* xri_tag; int /*<<< orphan*/  initial_transfer_length; scalar_t__ payload_offset_length; scalar_t__ fcp_cmd_buffer_length; TYPE_4__ bde; void* xbl; void* dbde; } ;
typedef  TYPE_11__ sli4_fcp_iwrite64_wqe_t ;
struct TYPE_22__ {int fc_id; scalar_t__ node; scalar_t__ node_group; } ;
typedef  TYPE_12__ ocs_remote_node_t ;
struct TYPE_23__ {scalar_t__ fcp2device; } ;
typedef  TYPE_13__ ocs_node_t ;
struct TYPE_24__ {int /*<<< orphan*/  phys; scalar_t__ size; TYPE_10__* virt; } ;
typedef  TYPE_14__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 void* SLI4_BDE_TYPE_BDE_64 ; 
 void* SLI4_BDE_TYPE_BLP ; 
 int /*<<< orphan*/  SLI4_CMD_FCP_IWRITE64_WQE ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_RPI ; 
 int /*<<< orphan*/  SLI4_SGE_TYPE_SKIP ; 
 int /*<<< orphan*/  SLI4_WQE_FCP_IWRITE64 ; 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,TYPE_14__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_fcp_iwrite64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *sgl, uint32_t first_data_sge,
		     uint32_t xfer_len, uint32_t first_burst, uint16_t xri, uint16_t tag, uint16_t cq_id,
		     uint32_t rpi, ocs_remote_node_t *rnode,
		     uint8_t dif, uint8_t bs, uint8_t timeout)
{
	sli4_fcp_iwrite64_wqe_t *iwrite = buf;
	sli4_sge_t	*sge = NULL;

	ocs_memset(buf, 0, size);

	if (!sgl || !sgl->virt) {
		ocs_log_err(sli4->os, "bad parameter sgl=%p virt=%p\n",
			    sgl, sgl ? sgl->virt : NULL);
		return -1;
	}
	sge = sgl->virt;

	if (sli4->config.sgl_pre_registered) {
		iwrite->xbl = FALSE;

		iwrite->dbde = TRUE;
		iwrite->bde.bde_type = SLI4_BDE_TYPE_BDE_64;

		iwrite->bde.buffer_length = sge[0].buffer_length;
		iwrite->bde.u.data.buffer_address_low  = sge[0].buffer_address_low;
		iwrite->bde.u.data.buffer_address_high = sge[0].buffer_address_high;
	} else {
		iwrite->xbl = TRUE;

		iwrite->bde.bde_type = SLI4_BDE_TYPE_BLP;

		iwrite->bde.buffer_length = sgl->size;
		iwrite->bde.u.blp.sgl_segment_address_low  = ocs_addr32_lo(sgl->phys);
		iwrite->bde.u.blp.sgl_segment_address_high = ocs_addr32_hi(sgl->phys);

		/* fill out fcp_cmnd buffer len and change resp buffer to be of type
		 * "skip" (note: response will still be written to sge[1] if necessary) */
		iwrite->fcp_cmd_buffer_length = sge[0].buffer_length;
		sge[1].sge_type = SLI4_SGE_TYPE_SKIP;
	}

	iwrite->payload_offset_length = sge[0].buffer_length + sge[1].buffer_length;
	iwrite->total_transfer_length = xfer_len;
	iwrite->initial_transfer_length = MIN(xfer_len, first_burst);

	iwrite->xri_tag = xri;
	iwrite->context_tag = rpi;

	iwrite->timer = timeout;

	iwrite->pu = 2;	/* WQE word 4 contains read transfer length */
	iwrite->class = SLI4_ELS_REQUEST64_CLASS_3;
	iwrite->command = SLI4_WQE_FCP_IWRITE64;
	iwrite->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
	iwrite->dif = dif;
	iwrite->bs  = bs;

	iwrite->abort_tag = xri;

	iwrite->request_tag = tag;
	iwrite->len_loc = 3;
	if (rnode->node_group) {
		iwrite->hlm = TRUE;
		iwrite->remote_n_port_id = rnode->fc_id & 0x00ffffff;
	}
	if (((ocs_node_t *)rnode->node)->fcp2device) {
		iwrite->erp = TRUE;
	}
	iwrite->cmd_type = SLI4_CMD_FCP_IWRITE64_WQE;
	iwrite->cq_id = cq_id;

	if (sli4->config.perf_hint) {
		iwrite->first_data_bde.bde_type = SLI4_BDE_TYPE_BDE_64;
		iwrite->first_data_bde.buffer_length = sge[first_data_sge].buffer_length;
		iwrite->first_data_bde.u.data.buffer_address_low  = sge[first_data_sge].buffer_address_low;
		iwrite->first_data_bde.u.data.buffer_address_high = sge[first_data_sge].buffer_address_high;
	}

	return  0;
}