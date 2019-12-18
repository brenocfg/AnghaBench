#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {scalar_t__ port_type; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_8__ {int request_length; scalar_t__ version; scalar_t__ timeout; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {scalar_t__ buffer_length; scalar_t__ buf_addr_high; scalar_t__ buf_addr_low; void* fdb; void* qry; void* blp; TYPE_1__ hdr; } ;
typedef  TYPE_3__ sli4_req_common_set_dump_location_t ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  phys; } ;
typedef  TYPE_4__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_OPC_COMMON_SET_DUMP_LOCATION ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 scalar_t__ ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int sli_cmd_sli_config (TYPE_2__*,void*,size_t,int,int /*<<< orphan*/ *) ; 

int32_t
sli_cmd_common_set_dump_location(sli4_t *sli4, void *buf, size_t size,
				 uint8_t query, uint8_t is_buffer_list,
				 ocs_dma_t *buffer, uint8_t fdb)
{
	sli4_req_common_set_dump_location_t *set_dump_loc = NULL;
	uint32_t	sli_config_off = 0;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size,
				sizeof (sli4_req_common_set_dump_location_t),
				NULL);
	}

	set_dump_loc = (sli4_req_common_set_dump_location_t *)((uint8_t *)buf + sli_config_off);

	set_dump_loc->hdr.opcode = SLI4_OPC_COMMON_SET_DUMP_LOCATION;
	set_dump_loc->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
	set_dump_loc->hdr.request_length = sizeof(sli4_req_common_set_dump_location_t) - sizeof(sli4_req_hdr_t);
	set_dump_loc->hdr.timeout = 0;
	set_dump_loc->hdr.version = 0;

	set_dump_loc->blp = is_buffer_list;
	set_dump_loc->qry = query;
	set_dump_loc->fdb = fdb;

	if (buffer) {
		set_dump_loc->buf_addr_low = ocs_addr32_lo(buffer->phys);
		set_dump_loc->buf_addr_high = ocs_addr32_hi(buffer->phys);
		set_dump_loc->buffer_length = buffer->len;
	} else {
		set_dump_loc->buf_addr_low = 0;
		set_dump_loc->buf_addr_high = 0;
		set_dump_loc->buffer_length = 0;
	}

	return(sli_config_off + sizeof(sli4_req_common_set_dump_location_t));
}