#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int if_type; scalar_t__ port_type; int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_res_common_get_port_name_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_6__ {int request_length; int version; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int pt; TYPE_1__ hdr; } ;
typedef  TYPE_3__ sli4_req_common_get_port_name_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  SLI4_IF_TYPE_BE3_SKH_PF 131 
#define  SLI4_IF_TYPE_BE3_SKH_VF 130 
#define  SLI4_IF_TYPE_LANCER_FC_ETH 129 
#define  SLI4_IF_TYPE_LANCER_RDMA 128 
 int /*<<< orphan*/  SLI4_OPC_COMMON_GET_PORT_NAME ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 int max (int,int) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int sli_cmd_sli_config (TYPE_2__*,void*,size_t,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
sli_cmd_common_get_port_name(sli4_t *sli4, void *buf, size_t size)
{
	sli4_req_common_get_port_name_t	*port_name;
	uint32_t	sli_config_off = 0;
	uint32_t	payload_size;
	uint8_t		version = 0;
	uint8_t		pt = 0;

	/* Select command version according to IF_TYPE */
	switch (sli4->if_type) {
	case SLI4_IF_TYPE_BE3_SKH_PF:
	case SLI4_IF_TYPE_BE3_SKH_VF:
		version = 0;
		break;
	case SLI4_IF_TYPE_LANCER_FC_ETH:
	case SLI4_IF_TYPE_LANCER_RDMA:
		version = 1;
		break;
	default:
		ocs_log_test(sli4->os, "unsupported IF_TYPE %d\n", sli4->if_type);
		return 0;
	}

	/* Payload length must accommodate both request and response */
	payload_size = max(sizeof(sli4_req_common_get_port_name_t),
			   sizeof(sli4_res_common_get_port_name_t));

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size,
				payload_size,
				NULL);

		pt = 1;
	}

	port_name = (sli4_req_common_get_port_name_t *)((uint8_t *)buf + sli_config_off);

	port_name->hdr.opcode		= SLI4_OPC_COMMON_GET_PORT_NAME;
	port_name->hdr.subsystem	= SLI4_SUBSYSTEM_COMMON;
	port_name->hdr.request_length	= sizeof(sli4_req_hdr_t) + (version * sizeof(uint32_t));
	port_name->hdr.version		= version;

	/* Set the port type value (ethernet=0, FC=1) for V1 commands */
	if (version == 1) {
		port_name->pt = pt;
	}

	return sli_config_off + port_name->hdr.request_length;
}