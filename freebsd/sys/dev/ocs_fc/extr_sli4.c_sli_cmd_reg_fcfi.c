#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_8__ {int /*<<< orphan*/  type_match; int /*<<< orphan*/  type_mask; int /*<<< orphan*/  r_ctl_match; int /*<<< orphan*/  r_ctl_mask; int /*<<< orphan*/  rq_id; } ;
typedef  TYPE_3__ sli4_cmd_rq_cfg_t ;
struct TYPE_6__ {int /*<<< orphan*/  command; } ;
struct TYPE_9__ {void* vlan_tag; int /*<<< orphan*/  vv; TYPE_2__* rq_cfg; int /*<<< orphan*/  rq_id_3; int /*<<< orphan*/  rq_id_2; int /*<<< orphan*/  rq_id_1; int /*<<< orphan*/  rq_id_0; void* fcf_index; TYPE_1__ hdr; } ;
typedef  TYPE_4__ sli4_cmd_reg_fcfi_t ;
typedef  int int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  type_match; int /*<<< orphan*/  type_mask; int /*<<< orphan*/  r_ctl_match; int /*<<< orphan*/  r_ctl_mask; } ;

/* Variables and functions */
 int SLI4_CMD_REG_FCFI_NUM_RQ_CFG ; 
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_REG_FCFI ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_reg_fcfi(sli4_t *sli4, void *buf, size_t size, uint16_t index, sli4_cmd_rq_cfg_t rq_cfg[SLI4_CMD_REG_FCFI_NUM_RQ_CFG], uint16_t vlan_id)
{
	sli4_cmd_reg_fcfi_t	*reg_fcfi = buf;
	uint32_t		i;

	ocs_memset(buf, 0, size);

	reg_fcfi->hdr.command = SLI4_MBOX_COMMAND_REG_FCFI;

	reg_fcfi->fcf_index = index;

	for (i = 0; i < SLI4_CMD_REG_FCFI_NUM_RQ_CFG; i++) {
		switch(i) {
		case 0:	reg_fcfi->rq_id_0 = rq_cfg[0].rq_id; break;
		case 1:	reg_fcfi->rq_id_1 = rq_cfg[1].rq_id; break;
		case 2:	reg_fcfi->rq_id_2 = rq_cfg[2].rq_id; break;
		case 3:	reg_fcfi->rq_id_3 = rq_cfg[3].rq_id; break;
		}
		reg_fcfi->rq_cfg[i].r_ctl_mask = rq_cfg[i].r_ctl_mask;
		reg_fcfi->rq_cfg[i].r_ctl_match = rq_cfg[i].r_ctl_match;
		reg_fcfi->rq_cfg[i].type_mask = rq_cfg[i].type_mask;
		reg_fcfi->rq_cfg[i].type_match = rq_cfg[i].type_match;
	}

	if (vlan_id) {
		reg_fcfi->vv = TRUE;
		reg_fcfi->vlan_tag = vlan_id;
	}

	return sizeof(sli4_cmd_reg_fcfi_t);
}