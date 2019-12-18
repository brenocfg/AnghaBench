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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {scalar_t__ port_type; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_res_hdr_t ;
typedef  int /*<<< orphan*/  sli4_req_hdr_t ;
struct TYPE_6__ {int request_length; int /*<<< orphan*/  subsystem; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int /*<<< orphan*/  eq_id; TYPE_1__ hdr; } ;
typedef  TYPE_3__ sli4_req_common_destroy_eq_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_OPC_COMMON_DESTROY_EQ ; 
 scalar_t__ SLI4_PORT_TYPE_FC ; 
 int /*<<< orphan*/  SLI4_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  max (int,int) ; 
 int sli_cmd_sli_config (TYPE_2__*,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
sli_cmd_common_destroy_eq(sli4_t *sli4, void *buf, size_t size, uint16_t eq_id)
{
	sli4_req_common_destroy_eq_t	*eq = NULL;
	uint32_t	sli_config_off = 0;

	if (SLI4_PORT_TYPE_FC == sli4->port_type) {
		sli_config_off = sli_cmd_sli_config(sli4, buf, size,
				/* Payload length must accommodate both request and response */
				max(sizeof(sli4_req_common_destroy_eq_t),
					sizeof(sli4_res_hdr_t)),
				NULL);
	}
	eq = (sli4_req_common_destroy_eq_t *)((uint8_t *)buf + sli_config_off);

	eq->hdr.opcode = SLI4_OPC_COMMON_DESTROY_EQ;
	eq->hdr.subsystem = SLI4_SUBSYSTEM_COMMON;
	eq->hdr.request_length = sizeof(sli4_req_common_destroy_eq_t) -
					sizeof(sli4_req_hdr_t);

	eq->eq_id = eq_id;

	return(sli_config_off + sizeof(sli4_req_common_destroy_eq_t));
}