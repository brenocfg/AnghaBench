#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {scalar_t__ port_type; } ;
typedef  TYPE_1__ sli4_t ;
struct TYPE_10__ {int /*<<< orphan*/  request_length; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_2__ sli4_req_hdr_t ;
struct TYPE_11__ {int /*<<< orphan*/  size; TYPE_2__* virt; } ;
typedef  TYPE_3__ ocs_dma_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_OPC_COMMON_GET_CNTL_ATTRIBUTES ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  ocs_memset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_cmd_sli_config (TYPE_1__*,void*,size_t,int,TYPE_3__*) ; 

__attribute__((used)) static int32_t
sli_cmd_common_get_cntl_attributes(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *dma)
{
	sli4_req_hdr_t *hdr = NULL;
	uint32_t	sli_config_off = 0;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size,
				sizeof(sli4_req_hdr_t),
				dma);
	}

	if (dma == NULL) {
		return 0;
	}

	ocs_memset(dma->virt, 0, dma->size);

	hdr = dma->virt;

	hdr->opcode = SLI4_OPC_COMMON_GET_CNTL_ATTRIBUTES;
	hdr->subsystem = SLI4_SUBSYSTEM_COMMON;
	hdr->request_length = dma->size;

	return(sli_config_off + sizeof(sli4_req_hdr_t));
}