#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_15__ {TYPE_1__* extent; } ;
struct TYPE_18__ {TYPE_2__ config; int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_16__ {int request_length; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_19__ {int page_count; TYPE_4__* page_descriptor; scalar_t__ rpi_offset; TYPE_3__ hdr; } ;
typedef  TYPE_6__ sli4_req_fcoe_post_hdr_templates_t ;
typedef  int /*<<< orphan*/  sli4_physical_page_descriptor_t ;
struct TYPE_20__ {uintptr_t phys; scalar_t__ virt; int /*<<< orphan*/  size; } ;
typedef  TYPE_7__ ocs_dma_t ;
typedef  int int32_t ;
struct TYPE_17__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_14__ {scalar_t__* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_OPC_FCOE_POST_HDR_TEMPLATES ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_FCFCOE ; 
 scalar_t__ SLI_PAGE_SIZE ; 
 size_t SLI_RSRC_FCOE_RPI ; 
 scalar_t__ UINT16_MAX ; 
 int /*<<< orphan*/  ocs_addr32_hi (uintptr_t) ; 
 int /*<<< orphan*/  ocs_addr32_lo (uintptr_t) ; 
 scalar_t__ ocs_dma_alloc (int /*<<< orphan*/ ,TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int sli_cmd_sli_config (TYPE_5__*,void*,size_t,int,TYPE_7__*) ; 
 int sli_page_count (int /*<<< orphan*/ ,scalar_t__) ; 

int32_t
sli_cmd_fcoe_post_hdr_templates(sli4_t *sli4, void *buf, size_t size,
		ocs_dma_t *dma, uint16_t rpi, ocs_dma_t *payload_dma)
{
	sli4_req_fcoe_post_hdr_templates_t *template = NULL;
	uint32_t	sli_config_off = 0;
	uintptr_t	phys = 0;
	uint32_t	i = 0;
	uint32_t	page_count;
	uint32_t	payload_size;

	page_count = sli_page_count(dma->size, SLI_PAGE_SIZE);

	payload_size = sizeof(sli4_req_fcoe_post_hdr_templates_t) +
				page_count * sizeof(sli4_physical_page_descriptor_t);

	if (page_count > 16) {
		/* We can't fit more than 16 descriptors into an embedded mailbox
		   command, it has to be non-embedded */
		if (ocs_dma_alloc(sli4->os, payload_dma, payload_size, 4)) {
			ocs_log_err(sli4->os, "mailbox payload memory allocation fail\n");
			return 0;
		}
		sli_config_off = sli_cmd_sli_config(sli4, buf, size, payload_size, payload_dma);
		template = (sli4_req_fcoe_post_hdr_templates_t *)payload_dma->virt;
	} else {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size, payload_size, NULL);
		template = (sli4_req_fcoe_post_hdr_templates_t *)((uint8_t *)buf + sli_config_off);
	}

	if (UINT16_MAX == rpi) {
		rpi = sli4->config.extent[SLI_RSRC_FCOE_RPI].base[0];
	}

	template->hdr.opcode = SLI4_OPC_FCOE_POST_HDR_TEMPLATES;
	template->hdr.subsystem = SLI4_SUBSYSTEM_FCFCOE;
	template->hdr.request_length = sizeof(sli4_req_fcoe_post_hdr_templates_t) -
					sizeof(sli4_req_hdr_t);

	template->rpi_offset = rpi;
	template->page_count = page_count;
	phys = dma->phys;
	for (i = 0; i < template->page_count; i++) {
		template->page_descriptor[i].low  = ocs_addr32_lo(phys);
		template->page_descriptor[i].high = ocs_addr32_hi(phys);

		phys += SLI_PAGE_SIZE;
	}

	return(sli_config_off + payload_size);
}