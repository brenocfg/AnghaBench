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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ port_type; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_6__ {int request_length; scalar_t__ version; scalar_t__ timeout; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int feature; int param_len; int /*<<< orphan*/  params; TYPE_1__ hdr; } ;
typedef  TYPE_3__ sli4_req_common_set_features_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_OPC_COMMON_SET_FEATURES ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int sli_cmd_sli_config (TYPE_2__*,void*,size_t,int,int /*<<< orphan*/ *) ; 

int32_t
sli_cmd_common_set_features(sli4_t *sli4, void *buf, size_t size,
			    uint32_t feature,
			    uint32_t param_len,
			    void* parameter)
{
	sli4_req_common_set_features_t *cmd = NULL;
	uint32_t	sli_config_off = 0;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size,
				sizeof (sli4_req_common_set_features_t),
				NULL);
	}

	cmd = (sli4_req_common_set_features_t *)((uint8_t *)buf + sli_config_off);

	cmd->hdr.opcode = SLI4_OPC_COMMON_SET_FEATURES;
	cmd->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
	cmd->hdr.request_length = sizeof(sli4_req_common_set_features_t) - sizeof(sli4_req_hdr_t);
	cmd->hdr.timeout = 0;
	cmd->hdr.version = 0;

	cmd->feature = feature;
	cmd->param_len = param_len;
	ocs_memcpy(cmd->params, parameter, param_len);

	return(sli_config_off + sizeof(sli4_req_common_set_features_t));
}