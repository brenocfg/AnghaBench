#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_11__ {scalar_t__ rq_min_buf_size; scalar_t__ rq_max_buf_size; } ;
struct TYPE_13__ {scalar_t__ port_type; TYPE_2__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_4__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_res_common_create_queue_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_10__ {int request_length; int version; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_14__ {scalar_t__ num_pages; int rqe_count; TYPE_3__* page_physical_address; scalar_t__ cq_id; scalar_t__ buffer_size; int /*<<< orphan*/  page_size; int /*<<< orphan*/  rqe_size; int /*<<< orphan*/  dnb; TYPE_1__ hdr; } ;
typedef  TYPE_5__ sli4_req_fcoe_rq_create_v1_t ;
struct TYPE_15__ {int size; uintptr_t phys; } ;
typedef  TYPE_6__ ocs_dma_t ;
typedef  int int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;

/* Variables and functions */
 int SLI4_FCOE_RQE_SIZE ; 
 int /*<<< orphan*/  SLI4_FCOE_RQE_SIZE_8 ; 
 scalar_t__ SLI4_FCOE_RQ_CREATE_V1_MAX_PAGES ; 
 int /*<<< orphan*/  SLI4_FCOE_RQ_PAGE_SIZE_4096 ; 
 int /*<<< orphan*/  SLI4_OPC_FCOE_RQ_CREATE ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_FCFCOE ; 
 scalar_t__ SLI_PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int max (int,int) ; 
 int /*<<< orphan*/  ocs_addr32_hi (uintptr_t) ; 
 int /*<<< orphan*/  ocs_addr32_lo (uintptr_t) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int sli_cmd_sli_config (TYPE_4__*,void*,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sli_page_count (int,scalar_t__) ; 

int32_t
sli_cmd_fcoe_rq_create_v1(sli4_t *sli4, void *buf, size_t size,
			  ocs_dma_t *qmem, uint16_t cq_id, uint16_t ulp,
			  uint16_t buffer_size)
{
	sli4_req_fcoe_rq_create_v1_t	*rq = NULL;
	uint32_t	sli_config_off = 0;
	uint32_t	p;
	uintptr_t	addr;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		uint32_t payload_size;

		/* Payload length must accommodate both request and response */
		payload_size = max(sizeof(sli4_req_fcoe_rq_create_v1_t),
				sizeof(sli4_res_common_create_queue_t));

		sli_config_off = sli_cmd_sli_config(sli4, buf, size, payload_size,
				NULL);
	}
	rq = (sli4_req_fcoe_rq_create_v1_t *)((uint8_t *)buf + sli_config_off);

	rq->hdr.opcode = SLI4_OPC_FCOE_RQ_CREATE;
	rq->hdr.subsystem = SLI4_SUBSYSTEM_FCFCOE;
	rq->hdr.request_length = sizeof(sli4_req_fcoe_rq_create_v1_t) -
					sizeof(sli4_req_hdr_t);
	rq->hdr.version = 1;

	/* Disable "no buffer warnings" to avoid Lancer bug */
	rq->dnb = TRUE;

	/* valid values for number of pages: 1-8 (sec 4.5.6) */
	rq->num_pages = sli_page_count(qmem->size, SLI_PAGE_SIZE);
	if (!rq->num_pages || (rq->num_pages > SLI4_FCOE_RQ_CREATE_V1_MAX_PAGES)) {
		ocs_log_test(sli4->os, "num_pages %d not valid, max %d\n",
                rq->num_pages, SLI4_FCOE_RQ_CREATE_V1_MAX_PAGES);
		return 0;
	}

	/*
	 * RQE count is the total number of entries (note not lg2(# entries))
	 */
	rq->rqe_count = qmem->size / SLI4_FCOE_RQE_SIZE;

	rq->rqe_size = SLI4_FCOE_RQE_SIZE_8;

	rq->page_size = SLI4_FCOE_RQ_PAGE_SIZE_4096;

	if ((buffer_size < sli4->config.rq_min_buf_size) ||
	    (buffer_size > sli4->config.rq_max_buf_size)) {
		ocs_log_err(sli4->os, "buffer_size %d out of range (%d-%d)\n",
				buffer_size,
				sli4->config.rq_min_buf_size,
				sli4->config.rq_max_buf_size);
		return -1;
	}
	rq->buffer_size = buffer_size;

	rq->cq_id = cq_id;

	for (p = 0, addr = qmem->phys;
			p < rq->num_pages;
			p++, addr += SLI_PAGE_SIZE) {
		rq->page_physical_address[p].low  = ocs_addr32_lo(addr);
		rq->page_physical_address[p].high = ocs_addr32_hi(addr);
	}

	return(sli_config_off + sizeof(sli4_req_fcoe_rq_create_v1_t));
}