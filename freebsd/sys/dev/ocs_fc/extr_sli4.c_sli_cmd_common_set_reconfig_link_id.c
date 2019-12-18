#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_10__ {scalar_t__ port_type; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_res_common_set_reconfig_link_id_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_9__ {int request_length; scalar_t__ version; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int fd; int next_link_config_id; TYPE_1__ hdr; } ;
typedef  TYPE_3__ sli4_req_common_set_reconfig_link_id_t ;
struct TYPE_12__ {int size; TYPE_3__* virt; } ;
typedef  TYPE_4__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_OPC_COMMON_SET_RECONFIG_LINK_ID ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 int max (int,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int sli_cmd_sli_config (TYPE_2__*,void*,size_t,int,int /*<<< orphan*/ *) ; 

int32_t
sli_cmd_common_set_reconfig_link_id(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *dma,
                                  uint32_t fd, uint32_t active_link_config_id)
{
        sli4_req_common_set_reconfig_link_id_t *req = NULL;
        uint32_t cmd_off = 0;
        uint32_t payload_size;

        /* Payload length must accommodate both request and response */
        payload_size = max(sizeof(sli4_req_common_set_reconfig_link_id_t),
                           sizeof(sli4_res_common_set_reconfig_link_id_t));

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		cmd_off = sli_cmd_sli_config(sli4, buf, size,
				payload_size,
				NULL);
	}

		if (dma != NULL) {
		req = dma->virt;
		ocs_memset(req, 0, dma->size);
		payload_size = dma->size;
	} else {
		req = (sli4_req_common_set_reconfig_link_id_t *)((uint8_t *)buf + cmd_off);
		payload_size = sizeof(sli4_req_common_set_reconfig_link_id_t);
	}

        req->hdr.opcode = SLI4_OPC_COMMON_SET_RECONFIG_LINK_ID;
        req->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
        req->hdr.request_length = payload_size - sizeof(sli4_req_hdr_t);
        req->hdr.version = 0;
        req->fd = fd;
        req->next_link_config_id = active_link_config_id;

        return(cmd_off + sizeof(sli4_req_common_set_reconfig_link_id_t));
}