#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  void* uint16_t ;
struct TYPE_32__ {scalar_t__ wqe_size; scalar_t__ perf_hint; scalar_t__ sgl_pre_registered; } ;
struct TYPE_21__ {TYPE_6__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_10__ sli4_t ;
struct TYPE_22__ {scalar_t__ buffer_length; int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
typedef  TYPE_11__ sli4_sge_t ;
struct TYPE_33__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_34__ {TYPE_7__ data; } ;
struct TYPE_35__ {scalar_t__ buffer_length; TYPE_8__ u; void* bde_type; } ;
struct TYPE_31__ {int dword; } ;
struct TYPE_28__ {int /*<<< orphan*/  sgl_segment_address_high; int /*<<< orphan*/  sgl_segment_address_low; } ;
struct TYPE_27__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_29__ {TYPE_2__ blp; TYPE_1__ data; } ;
struct TYPE_30__ {scalar_t__ buffer_length; TYPE_3__ u; void* bde_type; } ;
struct TYPE_23__ {scalar_t__ payload_offset_length; int dif; int bs; int iod; int len_loc; int ccpe; int ccp; int app_id_valid; int wqes; int /*<<< orphan*/  eat; TYPE_9__ first_data_bde; scalar_t__ fcp_data_receive_length; void* cq_id; int /*<<< orphan*/  cmd_type; TYPE_5__ dword5; void* hlm; void* request_tag; void* remote_xid; int /*<<< orphan*/  ct; int /*<<< orphan*/  class; int /*<<< orphan*/  command; void* ar; void* pu; scalar_t__ context_tag; void* xri_tag; void* xc; scalar_t__ relative_offset; TYPE_4__ bde; void* dbde; void* xbl; } ;
typedef  TYPE_12__ sli4_fcp_treceive64_wqe_t ;
struct TYPE_24__ {scalar_t__* dw; } ;
typedef  TYPE_13__ sli4_fcp_128byte_wqe_t ;
struct TYPE_25__ {int fc_id; scalar_t__ node_group; } ;
typedef  TYPE_14__ ocs_remote_node_t ;
struct TYPE_26__ {scalar_t__ size; int /*<<< orphan*/  phys; TYPE_11__* virt; } ;
typedef  TYPE_15__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 void* FALSE ; 
 void* SLI4_BDE_TYPE_BDE_64 ; 
 void* SLI4_BDE_TYPE_BLP ; 
 int /*<<< orphan*/  SLI4_CMD_FCP_TRECEIVE64_WQE ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_RPI ; 
 scalar_t__ SLI4_IO_AUTO_GOOD_RESPONSE ; 
 scalar_t__ SLI4_IO_CONTINUATION ; 
 int SLI4_MASK_CCP ; 
 scalar_t__ SLI4_WQE_EXT_BYTES ; 
 int /*<<< orphan*/  SLI4_WQE_FCP_TRECEIVE64 ; 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,TYPE_15__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_fcp_treceive64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *sgl, uint32_t first_data_sge,
		       uint32_t relative_off, uint32_t xfer_len, uint16_t xri, uint16_t tag, uint16_t cq_id,
		       uint16_t xid, uint32_t rpi, ocs_remote_node_t *rnode, uint32_t flags, uint8_t dif, uint8_t bs,
		       uint8_t csctl, uint32_t app_id)
{
	sli4_fcp_treceive64_wqe_t *trecv = buf;
	sli4_fcp_128byte_wqe_t *trecv_128 = buf;
	sli4_sge_t	*sge = NULL;

	ocs_memset(buf, 0, size);

	if (!sgl || !sgl->virt) {
		ocs_log_err(sli4->os, "bad parameter sgl=%p virt=%p\n",
			    sgl, sgl ? sgl->virt : NULL);
		return -1;
	}
	sge = sgl->virt;

	if (sli4->config.sgl_pre_registered) {
		trecv->xbl = FALSE;

		trecv->dbde = TRUE;
		trecv->bde.bde_type = SLI4_BDE_TYPE_BDE_64;

		trecv->bde.buffer_length = sge[0].buffer_length;
		trecv->bde.u.data.buffer_address_low  = sge[0].buffer_address_low;
		trecv->bde.u.data.buffer_address_high = sge[0].buffer_address_high;

		trecv->payload_offset_length = sge[0].buffer_length;
	} else {
		trecv->xbl = TRUE;

		/* if data is a single physical address, use a BDE */
		if (!dif && (xfer_len <= sge[2].buffer_length)) {
			trecv->dbde = TRUE;
			trecv->bde.bde_type = SLI4_BDE_TYPE_BDE_64;

			trecv->bde.buffer_length = sge[2].buffer_length;
			trecv->bde.u.data.buffer_address_low  = sge[2].buffer_address_low;
			trecv->bde.u.data.buffer_address_high = sge[2].buffer_address_high;
		} else {
			trecv->bde.bde_type = SLI4_BDE_TYPE_BLP;
			trecv->bde.buffer_length = sgl->size;
			trecv->bde.u.blp.sgl_segment_address_low  = ocs_addr32_lo(sgl->phys);
			trecv->bde.u.blp.sgl_segment_address_high = ocs_addr32_hi(sgl->phys);
		}
	}

	trecv->relative_offset = relative_off;

	if (flags & SLI4_IO_CONTINUATION) {
		trecv->xc = TRUE;
	}
	trecv->xri_tag = xri;

	trecv->context_tag = rpi;

	trecv->pu = TRUE;	/* WQE uses relative offset */

	if (flags & SLI4_IO_AUTO_GOOD_RESPONSE) {
		trecv->ar = TRUE;
	}

	trecv->command = SLI4_WQE_FCP_TRECEIVE64;
	trecv->class = SLI4_ELS_REQUEST64_CLASS_3;
	trecv->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
	trecv->dif = dif;
	trecv->bs  = bs;

	trecv->remote_xid = xid;

	trecv->request_tag = tag;

	trecv->iod = 1;

	trecv->len_loc = 0x2;

	if (rnode->node_group) {
		trecv->hlm = TRUE;
		trecv->dword5.dword = rnode->fc_id & 0x00ffffff;
	}

	trecv->cmd_type = SLI4_CMD_FCP_TRECEIVE64_WQE;

	trecv->cq_id = cq_id;

	trecv->fcp_data_receive_length = xfer_len;

	if (sli4->config.perf_hint) {
		trecv->first_data_bde.bde_type = SLI4_BDE_TYPE_BDE_64;
		trecv->first_data_bde.buffer_length = sge[first_data_sge].buffer_length;
		trecv->first_data_bde.u.data.buffer_address_low  = sge[first_data_sge].buffer_address_low;
		trecv->first_data_bde.u.data.buffer_address_high = sge[first_data_sge].buffer_address_high;
	}

	/* The upper 7 bits of csctl is the priority */
	if (csctl & SLI4_MASK_CCP) {
		trecv->ccpe = 1;
		trecv->ccp = (csctl & SLI4_MASK_CCP);
	}

	if (app_id && (sli4->config.wqe_size == SLI4_WQE_EXT_BYTES) && !trecv->eat) {
		trecv->app_id_valid = 1;
		trecv->wqes = 1;
		trecv_128->dw[31] = app_id;
	}
	return 0;
}