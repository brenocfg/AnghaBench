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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  void* uint16_t ;
struct TYPE_32__ {scalar_t__ wqe_size; scalar_t__ perf_hint; scalar_t__ sgl_pre_registered; } ;
struct TYPE_33__ {TYPE_8__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_9__ sli4_t ;
struct TYPE_20__ {scalar_t__ buffer_length; int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
typedef  TYPE_10__ sli4_sge_t ;
struct TYPE_29__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_30__ {TYPE_5__ data; } ;
struct TYPE_31__ {scalar_t__ buffer_length; TYPE_6__ u; void* bde_type; } ;
struct TYPE_26__ {int /*<<< orphan*/  sgl_segment_address_high; int /*<<< orphan*/  sgl_segment_address_low; } ;
struct TYPE_25__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_27__ {TYPE_2__ blp; TYPE_1__ data; } ;
struct TYPE_28__ {scalar_t__ buffer_length; TYPE_3__ u; void* bde_type; } ;
struct TYPE_21__ {int dif; int bs; int len_loc; int dword5; int ccpe; int ccp; int app_id_valid; int wqes; int /*<<< orphan*/  eat; TYPE_7__ first_data_bde; scalar_t__ fcp_data_transmit_length; int /*<<< orphan*/  cmd_type; void* cq_id; void* hlm; void* request_tag; void* remote_xid; int /*<<< orphan*/  ct; int /*<<< orphan*/  class; int /*<<< orphan*/  command; void* ar; void* pu; scalar_t__ rpi; void* xri_tag; void* xc; scalar_t__ relative_offset; TYPE_4__ bde; void* dbde; void* xbl; } ;
typedef  TYPE_11__ sli4_fcp_tsend64_wqe_t ;
struct TYPE_22__ {scalar_t__* dw; } ;
typedef  TYPE_12__ sli4_fcp_128byte_wqe_t ;
struct TYPE_23__ {int fc_id; scalar_t__ node_group; } ;
typedef  TYPE_13__ ocs_remote_node_t ;
struct TYPE_24__ {scalar_t__ size; int /*<<< orphan*/  phys; TYPE_10__* virt; } ;
typedef  TYPE_14__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 void* FALSE ; 
 void* SLI4_BDE_TYPE_BDE_64 ; 
 void* SLI4_BDE_TYPE_BLP ; 
 int /*<<< orphan*/  SLI4_CMD_FCP_TSEND64_WQE ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CONTEXT_RPI ; 
 scalar_t__ SLI4_IO_AUTO_GOOD_RESPONSE ; 
 scalar_t__ SLI4_IO_CONTINUATION ; 
 int SLI4_MASK_CCP ; 
 scalar_t__ SLI4_WQE_EXT_BYTES ; 
 int /*<<< orphan*/  SLI4_WQE_FCP_TSEND64 ; 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,TYPE_14__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_fcp_tsend64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *sgl, uint32_t first_data_sge,
		    uint32_t relative_off, uint32_t xfer_len,
		    uint16_t xri, uint16_t tag, uint16_t cq_id, uint16_t xid, uint32_t rpi, ocs_remote_node_t *rnode,
		    uint32_t flags, uint8_t dif, uint8_t bs, uint8_t csctl, uint32_t app_id)
{
	sli4_fcp_tsend64_wqe_t *tsend = buf;
	sli4_fcp_128byte_wqe_t *tsend_128 = buf;
	sli4_sge_t	*sge = NULL;

	ocs_memset(buf, 0, size);

	if (!sgl || !sgl->virt) {
		ocs_log_err(sli4->os, "bad parameter sgl=%p virt=%p\n",
			    sgl, sgl ? sgl->virt : NULL);
		return -1;
	}
	sge = sgl->virt;

	if (sli4->config.sgl_pre_registered) {
		tsend->xbl = FALSE;

		tsend->dbde = TRUE;
		tsend->bde.bde_type = SLI4_BDE_TYPE_BDE_64;

		/* TSEND64_WQE specifies first two SGE are skipped
		 * (i.e. 3rd is valid) */
		tsend->bde.buffer_length = sge[2].buffer_length;
		tsend->bde.u.data.buffer_address_low  = sge[2].buffer_address_low;
		tsend->bde.u.data.buffer_address_high = sge[2].buffer_address_high;
	} else {
		tsend->xbl = TRUE;

		/* if data is a single physical address, use a BDE */
		if (!dif && (xfer_len <= sge[2].buffer_length)) {
			tsend->dbde = TRUE;
			tsend->bde.bde_type = SLI4_BDE_TYPE_BDE_64;
			/* TSEND64_WQE specifies first two SGE are skipped
			 * (i.e. 3rd is valid) */
			tsend->bde.buffer_length = sge[2].buffer_length;
			tsend->bde.u.data.buffer_address_low  = sge[2].buffer_address_low;
			tsend->bde.u.data.buffer_address_high = sge[2].buffer_address_high;
		} else {
			tsend->bde.bde_type = SLI4_BDE_TYPE_BLP;
			tsend->bde.buffer_length = sgl->size;
			tsend->bde.u.blp.sgl_segment_address_low  = ocs_addr32_lo(sgl->phys);
			tsend->bde.u.blp.sgl_segment_address_high = ocs_addr32_hi(sgl->phys);
		}
	}

	tsend->relative_offset = relative_off;

	if (flags & SLI4_IO_CONTINUATION) {
		tsend->xc = TRUE;
	}
	tsend->xri_tag = xri;

	tsend->rpi = rpi;

	tsend->pu = TRUE;	/* WQE uses relative offset */

	if (flags & SLI4_IO_AUTO_GOOD_RESPONSE) {
		tsend->ar = TRUE;
	}

	tsend->command = SLI4_WQE_FCP_TSEND64;
	tsend->class = SLI4_ELS_REQUEST64_CLASS_3;
	tsend->ct = SLI4_ELS_REQUEST64_CONTEXT_RPI;
	tsend->dif = dif;
	tsend->bs  = bs;

	tsend->remote_xid = xid;

	tsend->request_tag = tag;

	tsend->len_loc = 0x2;

	if (rnode->node_group) {
		tsend->hlm = TRUE;
		tsend->dword5 = rnode->fc_id & 0x00ffffff;
	}

	tsend->cq_id = cq_id;

	tsend->cmd_type = SLI4_CMD_FCP_TSEND64_WQE;

	tsend->fcp_data_transmit_length = xfer_len;

	if (sli4->config.perf_hint) {
		tsend->first_data_bde.bde_type = SLI4_BDE_TYPE_BDE_64;
		tsend->first_data_bde.buffer_length = sge[first_data_sge].buffer_length;
		tsend->first_data_bde.u.data.buffer_address_low  = sge[first_data_sge].buffer_address_low;
		tsend->first_data_bde.u.data.buffer_address_high = sge[first_data_sge].buffer_address_high;
	}

	/* The upper 7 bits of csctl is the priority */
	if (csctl & SLI4_MASK_CCP) {
		tsend->ccpe = 1;
		tsend->ccp = (csctl & SLI4_MASK_CCP);
	}

	if (app_id && (sli4->config.wqe_size == SLI4_WQE_EXT_BYTES) && !tsend->eat) {
		tsend->app_id_valid = 1;
		tsend->wqes = 1;
		tsend_128->dw[31] = app_id;
	}
	return 0;
}