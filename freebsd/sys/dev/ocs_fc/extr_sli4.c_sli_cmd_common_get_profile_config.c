#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ port_type; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_10__ {int request_length; int version; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_12__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ sli4_req_common_get_profile_config_t ;
struct TYPE_13__ {int size; TYPE_3__* virt; } ;
typedef  TYPE_4__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_OPC_COMMON_GET_PROFILE_CONFIG ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  ocs_memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int sli_cmd_sli_config (TYPE_2__*,void*,size_t,int,TYPE_4__*) ; 

int32_t
sli_cmd_common_get_profile_config(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *dma)
{
        sli4_req_common_get_profile_config_t *req = NULL;
	uint32_t	sli_config_off = 0;
	uint32_t	payload_size;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size,
				sizeof (sli4_req_common_get_profile_config_t),
				dma);
	}

	if (dma != NULL) {
		req = dma->virt;
		ocs_memset(req, 0, dma->size);
		payload_size = dma->size;
	} else {
		req = (sli4_req_common_get_profile_config_t *)((uint8_t *)buf + sli_config_off);
		payload_size = sizeof(sli4_req_common_get_profile_config_t);
	}

        req->hdr.opcode = SLI4_OPC_COMMON_GET_PROFILE_CONFIG;
        req->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
        req->hdr.request_length = payload_size - sizeof(sli4_req_hdr_t);
        req->hdr.version = 1;

        return(sli_config_off + sizeof(sli4_req_common_get_profile_config_t));
}