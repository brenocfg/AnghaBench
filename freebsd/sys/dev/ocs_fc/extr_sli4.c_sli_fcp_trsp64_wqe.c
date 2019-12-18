#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct TYPE_18__ {scalar_t__ wqe_size; scalar_t__ sgl_pre_registered; } ;
struct TYPE_19__ {scalar_t__ if_type; TYPE_4__ config; } ;
typedef  TYPE_5__ sli4_t ;
struct TYPE_20__ {int buffer_length; int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
typedef  TYPE_6__ sli4_sge_t ;
struct TYPE_15__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_16__ {TYPE_1__ data; } ;
struct TYPE_17__ {int buffer_length; TYPE_2__ u; int /*<<< orphan*/  bde_type; } ;
struct TYPE_21__ {int fcp_response_length; int dword5; int rpi; int dnrx; int len_loc; int ccpe; int ccp; int app_id_valid; int wqes; int /*<<< orphan*/  eat; int /*<<< orphan*/  cmd_type; void* cq_id; void* request_tag; void* remote_xid; int /*<<< orphan*/  class; int /*<<< orphan*/  command; void* xri_tag; void* hlm; void* xc; TYPE_3__ bde; void* xbl; void* dbde; void* ag; } ;
typedef  TYPE_7__ sli4_fcp_trsp64_wqe_t ;
struct TYPE_22__ {int* dw; } ;
typedef  TYPE_8__ sli4_fcp_128byte_wqe_t ;
struct TYPE_23__ {int fc_id; scalar_t__ node_group; } ;
typedef  TYPE_9__ ocs_remote_node_t ;
struct TYPE_14__ {TYPE_6__* virt; } ;
typedef  TYPE_10__ ocs_dma_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_CMD_FCP_TRSP64_WQE ; 
 int /*<<< orphan*/  SLI4_ELS_REQUEST64_CLASS_3 ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 int SLI4_IO_AUTO_GOOD_RESPONSE ; 
 int SLI4_IO_CONTINUATION ; 
 int SLI4_IO_DNRX ; 
 int SLI4_MASK_CCP ; 
 scalar_t__ SLI4_WQE_EXT_BYTES ; 
 int /*<<< orphan*/  SLI4_WQE_FCP_TRSP64 ; 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_fcp_trsp64_wqe(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *sgl, uint32_t rsp_len,
		   uint16_t xri, uint16_t tag, uint16_t cq_id, uint16_t xid, uint32_t rpi, ocs_remote_node_t *rnode,
		   uint32_t flags, uint8_t csctl, uint8_t port_owned, uint32_t app_id)
{
	sli4_fcp_trsp64_wqe_t *trsp = buf;
	sli4_fcp_128byte_wqe_t *trsp_128 = buf;

	ocs_memset(buf, 0, size);

	if (flags & SLI4_IO_AUTO_GOOD_RESPONSE) {
		trsp->ag = TRUE;
		/*
		 * The SLI-4 documentation states that the BDE is ignored when
		 * using auto-good response, but, at least for IF_TYPE 0 devices,
		 * this does not appear to be true.
		 */
		if (SLI4_IF_TYPE_BE3_SKH_PF == sli4->if_type) {
			trsp->bde.buffer_length = 12;	/* byte size of RSP */
		}
	} else {
		sli4_sge_t	*sge = sgl->virt;

		if (sli4->config.sgl_pre_registered || port_owned) {
			trsp->dbde = TRUE;
		} else {
			trsp->xbl = TRUE;
		}

		trsp->bde.bde_type = SLI4_BDE_TYPE_BDE_64;
		trsp->bde.buffer_length = sge[0].buffer_length;
		trsp->bde.u.data.buffer_address_low  = sge[0].buffer_address_low;
		trsp->bde.u.data.buffer_address_high = sge[0].buffer_address_high;

		trsp->fcp_response_length = rsp_len;
	}

	if (flags & SLI4_IO_CONTINUATION) {
		trsp->xc = TRUE;
	}

	if (rnode->node_group) {
		trsp->hlm = TRUE;
		trsp->dword5 = rnode->fc_id & 0x00ffffff;
	}

	trsp->xri_tag = xri;
	trsp->rpi = rpi;

	trsp->command = SLI4_WQE_FCP_TRSP64;
	trsp->class = SLI4_ELS_REQUEST64_CLASS_3;

	trsp->remote_xid = xid;
	trsp->request_tag = tag;
	trsp->dnrx = ((flags & SLI4_IO_DNRX) == 0 ? 0 : 1);
	trsp->len_loc = 0x1;
	trsp->cq_id = cq_id;
	trsp->cmd_type = SLI4_CMD_FCP_TRSP64_WQE;

	/* The upper 7 bits of csctl is the priority */
	if (csctl & SLI4_MASK_CCP) {
		trsp->ccpe = 1;
		trsp->ccp = (csctl & SLI4_MASK_CCP);
	}

	if (app_id && (sli4->config.wqe_size == SLI4_WQE_EXT_BYTES) && !trsp->eat) {
		trsp->app_id_valid = 1;
		trsp->wqes = 1;
		trsp_128->dw[31] = app_id;
	}
	return 0;
}