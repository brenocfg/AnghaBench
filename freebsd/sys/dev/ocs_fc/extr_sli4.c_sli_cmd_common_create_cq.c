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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct TYPE_16__ {int if_type; scalar_t__ port_type; int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_res_common_create_queue_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_14__ {int version; int request_length; void* subsystem; void* opcode; } ;
struct TYPE_17__ {int page_size; int num_pages; int cqe_count; TYPE_4__* page_physical_address; void* eq_id; void* arm; void* valid; void* evt; void* cqecnt; TYPE_3__ hdr; } ;
typedef  TYPE_6__ sli4_req_common_create_cq_v2_t ;
struct TYPE_12__ {int request_length; int /*<<< orphan*/  version; void* subsystem; void* opcode; } ;
struct TYPE_18__ {int num_pages; TYPE_2__* page_physical_address; void* eq_id; void* arm; void* valid; void* evt; void* cqecnt; TYPE_1__ hdr; } ;
typedef  TYPE_7__ sli4_req_common_create_cq_v0_t ;
struct TYPE_19__ {int size; uintptr_t phys; } ;
typedef  TYPE_8__ ocs_dma_t ;
typedef  int int32_t ;
struct TYPE_15__ {void* high; void* low; } ;
struct TYPE_13__ {void* high; void* low; } ;

/* Variables and functions */
 void* FALSE ; 
 int SLI4_COMMON_CREATE_CQ_V2_MAX_PAGES ; 
 int SLI4_CQE_BYTES ; 
 void* SLI4_CQ_CNT_1024 ; 
 void* SLI4_CQ_CNT_256 ; 
 void* SLI4_CQ_CNT_512 ; 
 void* SLI4_CQ_CNT_LARGE ; 
#define  SLI4_IF_TYPE_BE3_SKH_PF 129 
#define  SLI4_IF_TYPE_LANCER_FC_ETH 128 
 void* SLI4_OPC_COMMON_CREATE_CQ ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 void* SLI4_SUBSYSTEM_COMMON ; 
 int SLI_PAGE_SIZE ; 
 void* TRUE ; 
 int max (size_t,int) ; 
 void* ocs_addr32_hi (uintptr_t) ; 
 void* ocs_addr32_lo (uintptr_t) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int sli_cmd_sli_config (TYPE_5__*,void*,size_t,int,int /*<<< orphan*/ *) ; 
 int sli_page_count (int,int) ; 

__attribute__((used)) static int32_t
sli_cmd_common_create_cq(sli4_t *sli4, void *buf, size_t size,
		ocs_dma_t *qmem, uint16_t eq_id, uint16_t ignored)
{
	sli4_req_common_create_cq_v0_t	*cqv0 = NULL;
	sli4_req_common_create_cq_v2_t	*cqv2 = NULL;
	uint32_t	sli_config_off = 0;
	uint32_t	p;
	uintptr_t	addr;
	uint32_t	if_type = sli4->if_type;
	uint32_t	page_bytes = 0;
	uint32_t	num_pages = 0;
	uint32_t 	cmd_size = 0;
	uint32_t	page_size = 0;
	uint32_t	n_cqe = 0;

	/* First calculate number of pages and the mailbox cmd length */
	switch (if_type)
	{
	case SLI4_IF_TYPE_BE3_SKH_PF:
		page_bytes = SLI_PAGE_SIZE;
		num_pages = sli_page_count(qmem->size, page_bytes);
		cmd_size = sizeof(sli4_req_common_create_cq_v0_t) + (8 * num_pages);
		break;
	case SLI4_IF_TYPE_LANCER_FC_ETH:
		n_cqe = qmem->size / SLI4_CQE_BYTES;
		switch (n_cqe) {
		case 256:
		case 512:
		case 1024:
		case 2048:
			page_size = 1;
			break;
		case 4096:
			page_size = 2;
			break;
		default:
			return 0;
		}
		page_bytes = page_size * SLI_PAGE_SIZE;
		num_pages = sli_page_count(qmem->size, page_bytes);
		cmd_size = sizeof(sli4_req_common_create_cq_v2_t) + (8 * num_pages);
		break;
	default:
		ocs_log_test(sli4->os, "unsupported IF_TYPE %d\n", if_type);
		return -1;
	}


	/* now that we have the mailbox command size, we can set SLI_CONFIG fields */
	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		uint32_t payload_size;

		/* Payload length must accommodate both request and response */
		payload_size = max((size_t)cmd_size, sizeof(sli4_res_common_create_queue_t));

		sli_config_off = sli_cmd_sli_config(sli4, buf, size, payload_size,
				NULL);
	}

	switch (if_type)
	{
	case SLI4_IF_TYPE_BE3_SKH_PF:
		cqv0 = (sli4_req_common_create_cq_v0_t *)((uint8_t *)buf + sli_config_off);
		cqv0->hdr.opcode = SLI4_OPC_COMMON_CREATE_CQ;
		cqv0->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
		cqv0->hdr.version = 0;
		cqv0->hdr.request_length = cmd_size - sizeof(sli4_req_hdr_t);

		/* valid values for number of pages: 1, 2, 4 (sec 4.4.3) */
		cqv0->num_pages = num_pages;
		switch (cqv0->num_pages) {
		case 1:
			cqv0->cqecnt = SLI4_CQ_CNT_256;
			break;
		case 2:
			cqv0->cqecnt = SLI4_CQ_CNT_512;
			break;
		case 4:
			cqv0->cqecnt = SLI4_CQ_CNT_1024;
			break;
		default:
			ocs_log_test(sli4->os, "num_pages %d not valid\n", cqv0->num_pages);
			return -1;
		}
		cqv0->evt = TRUE;
		cqv0->valid = TRUE;
		/* TODO cq->nodelay = ???; */
		/* TODO cq->clswm = ???; */
		cqv0->arm = FALSE;
		cqv0->eq_id = eq_id;

		for (p = 0, addr = qmem->phys;
				p < cqv0->num_pages;
				p++, addr += page_bytes) {
			cqv0->page_physical_address[p].low = ocs_addr32_lo(addr);
			cqv0->page_physical_address[p].high = ocs_addr32_hi(addr);
		}

		break;
	case SLI4_IF_TYPE_LANCER_FC_ETH:
	{
		cqv2 = (sli4_req_common_create_cq_v2_t *)((uint8_t *)buf + sli_config_off);
		cqv2->hdr.opcode = SLI4_OPC_COMMON_CREATE_CQ;
		cqv2->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
		cqv2->hdr.version = 2;
		cqv2->hdr.request_length = cmd_size - sizeof(sli4_req_hdr_t);

		cqv2->page_size = page_size;

		/* valid values for number of pages: 1, 2, 4, 8 (sec 4.4.3) */
		cqv2->num_pages = num_pages;
		if (!cqv2->num_pages || (cqv2->num_pages > SLI4_COMMON_CREATE_CQ_V2_MAX_PAGES)) {
			return 0;
		}

		switch (cqv2->num_pages) {
		case 1:
			cqv2->cqecnt = SLI4_CQ_CNT_256;
			break;
		case 2:
			cqv2->cqecnt = SLI4_CQ_CNT_512;
			break;
		case 4:
			cqv2->cqecnt = SLI4_CQ_CNT_1024;
			break;
		case 8:
			cqv2->cqecnt = SLI4_CQ_CNT_LARGE;
			cqv2->cqe_count = n_cqe;
			break;
		default:
			ocs_log_test(sli4->os, "num_pages %d not valid\n", cqv2->num_pages);
			return -1;
		}

		cqv2->evt = TRUE;
		cqv2->valid = TRUE;
		/* TODO cq->nodelay = ???; */
		/* TODO cq->clswm = ???; */
		cqv2->arm = FALSE;
		cqv2->eq_id = eq_id;

		for (p = 0, addr = qmem->phys;
				p < cqv2->num_pages;
				p++, addr += page_bytes) {
			cqv2->page_physical_address[p].low = ocs_addr32_lo(addr);
			cqv2->page_physical_address[p].high = ocs_addr32_hi(addr);
		}
	}
		break;
	}	

	return (sli_config_off + cmd_size);
}