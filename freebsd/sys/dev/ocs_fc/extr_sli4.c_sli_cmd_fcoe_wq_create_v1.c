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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int wqe_size; } ;
struct TYPE_13__ {scalar_t__ port_type; TYPE_2__ config; } ;
typedef  TYPE_4__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_res_common_create_queue_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_10__ {int request_length; int version; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_14__ {scalar_t__ num_pages; int page_size; int wqe_count; TYPE_3__* page_physical_address; int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  cq_id; TYPE_1__ hdr; } ;
typedef  TYPE_5__ sli4_req_fcoe_wq_create_v1_t ;
struct TYPE_15__ {int size; uintptr_t phys; } ;
typedef  TYPE_6__ ocs_dma_t ;
typedef  int int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;

/* Variables and functions */
 scalar_t__ SLI4_FCOE_WQ_CREATE_V1_MAX_PAGES ; 
 int /*<<< orphan*/  SLI4_OPC_FCOE_WQ_CREATE ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_FCFCOE ; 
 int SLI4_WQE_EXT_BYTES ; 
 int /*<<< orphan*/  SLI4_WQE_EXT_SIZE ; 
 int /*<<< orphan*/  SLI4_WQE_SIZE ; 
 int SLI_PAGE_SIZE ; 
 int max (int,int) ; 
 int /*<<< orphan*/  ocs_addr32_hi (uintptr_t) ; 
 int /*<<< orphan*/  ocs_addr32_lo (uintptr_t) ; 
 int sli_cmd_sli_config (TYPE_4__*,void*,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sli_page_count (int,int) ; 

int32_t
sli_cmd_fcoe_wq_create_v1(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *qmem,
			  uint16_t cq_id, uint16_t ignored)
{
	sli4_req_fcoe_wq_create_v1_t	*wq = NULL;
	uint32_t	sli_config_off = 0;
	uint32_t	p;
	uintptr_t	addr;
	uint32_t	page_size = 0;
	uint32_t	page_bytes = 0;
	uint32_t	n_wqe = 0;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		uint32_t payload_size;

		/* Payload length must accommodate both request and response */
		payload_size = max(sizeof(sli4_req_fcoe_wq_create_v1_t),
				sizeof(sli4_res_common_create_queue_t));

		sli_config_off = sli_cmd_sli_config(sli4, buf, size, payload_size,
				NULL);
	}
	wq = (sli4_req_fcoe_wq_create_v1_t *)((uint8_t *)buf + sli_config_off);

	wq->hdr.opcode = SLI4_OPC_FCOE_WQ_CREATE;
	wq->hdr.subsystem = SLI4_SUBSYSTEM_FCFCOE;
	wq->hdr.request_length = sizeof(sli4_req_fcoe_wq_create_v1_t) -
					sizeof(sli4_req_hdr_t);
	wq->hdr.version = 1;

	n_wqe = qmem->size / sli4->config.wqe_size;

	/* This heuristic to determine the page size is simplistic 
	 * but could be made more sophisticated
	 */
	switch (qmem->size) {
	case 4096:
	case 8192:
	case 16384:
	case 32768:
		page_size = 1;
		break;
	case 65536:
		page_size = 2;
		break;
	case 131072:
		page_size = 4;
		break;
	case 262144:
		page_size = 8;
		break;
	case 524288:
		page_size = 10;
		break;
	default:
		return 0;
	}
	page_bytes = page_size * SLI_PAGE_SIZE;

	/* valid values for number of pages: 1-8 */
	wq->num_pages = sli_page_count(qmem->size, page_bytes);
	if (!wq->num_pages || (wq->num_pages > SLI4_FCOE_WQ_CREATE_V1_MAX_PAGES)) {
		return 0;
	}

	wq->cq_id = cq_id;

	wq->page_size = page_size;

	if (sli4->config.wqe_size == SLI4_WQE_EXT_BYTES) {
		wq->wqe_size = SLI4_WQE_EXT_SIZE;
	} else {
		wq->wqe_size = SLI4_WQE_SIZE;
	}

	wq->wqe_count = n_wqe;

	for (p = 0, addr = qmem->phys;
			p < wq->num_pages;
			p++, addr += page_bytes) {
		wq->page_physical_address[p].low  = ocs_addr32_lo(addr);
		wq->page_physical_address[p].high = ocs_addr32_hi(addr);
	}

	return(sli_config_off + sizeof(sli4_req_fcoe_wq_create_v1_t));
}