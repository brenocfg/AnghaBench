#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_14__ {scalar_t__ port_type; } ;
typedef  TYPE_4__ sli4_t ;
struct TYPE_11__ {int request_length; scalar_t__ version; scalar_t__ timeout; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_15__ {int desired_read_length; int read_offset; int host_buffer_descriptor_count; scalar_t__ host_buffer_descriptor; int /*<<< orphan*/  object_name; TYPE_1__ hdr; } ;
typedef  TYPE_5__ sli4_req_common_read_object_t ;
struct TYPE_12__ {scalar_t__ buffer_address_high; scalar_t__ buffer_address_low; } ;
struct TYPE_13__ {TYPE_2__ data; } ;
struct TYPE_16__ {int buffer_length; TYPE_3__ u; int /*<<< orphan*/  bde_type; } ;
typedef  TYPE_6__ sli4_bde_t ;
struct TYPE_17__ {int /*<<< orphan*/  phys; } ;
typedef  TYPE_7__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_OPC_COMMON_READ_OBJECT ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 scalar_t__ ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int sli_cmd_sli_config (TYPE_4__*,void*,size_t,int,int /*<<< orphan*/ *) ; 

int32_t
sli_cmd_common_read_object(sli4_t *sli4, void *buf, size_t size,
		uint32_t desired_read_length,
		uint32_t offset,
		char *object_name,
		ocs_dma_t *dma)
{
	sli4_req_common_read_object_t *rd_obj = NULL;
	uint32_t	sli_config_off = 0;
	sli4_bde_t *host_buffer;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size,
				sizeof (sli4_req_common_read_object_t) + sizeof (sli4_bde_t),
				NULL);
	}

	rd_obj = (sli4_req_common_read_object_t *)((uint8_t *)buf + sli_config_off);

	rd_obj->hdr.opcode = SLI4_OPC_COMMON_READ_OBJECT;
	rd_obj->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
	rd_obj->hdr.request_length = sizeof(*rd_obj) - 4*sizeof(uint32_t) + sizeof(sli4_bde_t);
	rd_obj->hdr.timeout = 0;
	rd_obj->hdr.version = 0;

	rd_obj->desired_read_length = desired_read_length;
	rd_obj->read_offset = offset;
	ocs_strncpy(rd_obj->object_name, object_name, sizeof(rd_obj->object_name));
	rd_obj->host_buffer_descriptor_count = 1;

	host_buffer = (sli4_bde_t *)rd_obj->host_buffer_descriptor;

	/* Setup to transfer xfer_size bytes to device */
	host_buffer->bde_type = SLI4_BDE_TYPE_BDE_64;
	host_buffer->buffer_length = desired_read_length;
	if (dma != NULL) {
		host_buffer->u.data.buffer_address_low = ocs_addr32_lo(dma->phys);
		host_buffer->u.data.buffer_address_high = ocs_addr32_hi(dma->phys);
	} else {
		host_buffer->u.data.buffer_address_low = 0;
		host_buffer->u.data.buffer_address_high = 0;
	}


	return(sli_config_off + sizeof(sli4_req_common_read_object_t) + sizeof (sli4_bde_t));
}