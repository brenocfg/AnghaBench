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
typedef  void* uint16_t ;
struct TYPE_10__ {scalar_t__ mq_create_version; } ;
struct TYPE_13__ {scalar_t__ port_type; TYPE_1__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_4__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_res_common_create_queue_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_11__ {int request_length; int version; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_14__ {uintptr_t num_pages; TYPE_3__* page_physical_address; int /*<<< orphan*/  val; void* cq_id_v0; TYPE_2__ hdr; void* cq_id_v1; int /*<<< orphan*/  async_event_bitmap; int /*<<< orphan*/  ring_size; } ;
typedef  TYPE_5__ sli4_req_common_create_mq_ext_t ;
struct TYPE_15__ {uintptr_t size; uintptr_t phys; } ;
typedef  TYPE_6__ ocs_dma_t ;
typedef  int int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_ASYNC_EVT_FC_FCOE ; 
 int /*<<< orphan*/  SLI4_MQE_SIZE_128 ; 
 int /*<<< orphan*/  SLI4_MQE_SIZE_16 ; 
 int /*<<< orphan*/  SLI4_MQE_SIZE_32 ; 
 int /*<<< orphan*/  SLI4_MQE_SIZE_64 ; 
 int /*<<< orphan*/  SLI4_OPC_COMMON_CREATE_MQ_EXT ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 uintptr_t SLI_PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int max (int,int) ; 
 int /*<<< orphan*/  ocs_addr32_hi (uintptr_t) ; 
 int /*<<< orphan*/  ocs_addr32_lo (uintptr_t) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int sli_cmd_sli_config (TYPE_4__*,void*,size_t,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
sli_cmd_common_create_mq_ext(sli4_t *sli4, void *buf, size_t size,
			     ocs_dma_t *qmem, uint16_t cq_id, uint16_t ignored)
{
	sli4_req_common_create_mq_ext_t	*mq = NULL;
	uint32_t	sli_config_off = 0;
	uint32_t	p;
	uintptr_t	addr;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		uint32_t payload_size;

		/* Payload length must accommodate both request and response */
		payload_size = max(sizeof(sli4_req_common_create_mq_ext_t),
				sizeof(sli4_res_common_create_queue_t));

		sli_config_off = sli_cmd_sli_config(sli4, buf, size, payload_size,
				NULL);
	}
	mq = (sli4_req_common_create_mq_ext_t *)((uint8_t *)buf + sli_config_off);

	mq->hdr.opcode = SLI4_OPC_COMMON_CREATE_MQ_EXT;
	mq->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
	mq->hdr.request_length = sizeof(sli4_req_common_create_mq_ext_t) -
					sizeof(sli4_req_hdr_t);
	/* valid values for number of pages: 1, 2, 4, 8 (sec 4.4.12) */
	mq->num_pages = qmem->size / SLI_PAGE_SIZE;
	switch (mq->num_pages) {
	case 1:
		mq->ring_size = SLI4_MQE_SIZE_16;
		break;
	case 2:
		mq->ring_size = SLI4_MQE_SIZE_32;
		break;
	case 4:
		mq->ring_size = SLI4_MQE_SIZE_64;
		break;
	case 8:
		mq->ring_size = SLI4_MQE_SIZE_128;
		break;
	default:
		ocs_log_test(sli4->os, "num_pages %d not valid\n", mq->num_pages);
		return -1;
	}

	/* TODO break this down by sli4->config.topology */
	mq->async_event_bitmap = SLI4_ASYNC_EVT_FC_FCOE;

	if (sli4->config.mq_create_version) {
		mq->cq_id_v1 = cq_id;
		mq->hdr.version = 1;
	}
	else {
		mq->cq_id_v0 = cq_id;
	}
	mq->val = TRUE;

	for (p = 0, addr = qmem->phys;
			p < mq->num_pages;
			p++, addr += SLI_PAGE_SIZE) {
		mq->page_physical_address[p].low = ocs_addr32_lo(addr);
		mq->page_physical_address[p].high = ocs_addr32_hi(addr);
	}

	return(sli_config_off + sizeof(sli4_req_common_create_mq_ext_t));
}