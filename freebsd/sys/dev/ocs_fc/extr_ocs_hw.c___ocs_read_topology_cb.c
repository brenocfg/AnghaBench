#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int link_speed; } ;
struct TYPE_9__ {scalar_t__ status; } ;
struct TYPE_13__ {int attention_type; int topology; TYPE_3__ link_current; int /*<<< orphan*/  acquired_al_pa; TYPE_1__ hdr; } ;
typedef  TYPE_5__ sli4_cmd_read_topology_t ;
struct TYPE_12__ {int speed; int /*<<< orphan*/ * loop_map; int /*<<< orphan*/  medium; int /*<<< orphan*/  topology; int /*<<< orphan*/  fc_id; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/ * virt; } ;
struct TYPE_14__ {int /*<<< orphan*/  os; TYPE_4__ link; TYPE_2__ loop_map; } ;
typedef  TYPE_6__ ocs_hw_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI4_FCOE_FCF_TABLE_FIRST ; 
#define  SLI4_READ_TOPOLOGY_FC_AL 138 
#define  SLI4_READ_TOPOLOGY_LINK_DOWN 137 
#define  SLI4_READ_TOPOLOGY_LINK_NO_ALPA 136 
#define  SLI4_READ_TOPOLOGY_LINK_UP 135 
#define  SLI4_READ_TOPOLOGY_NPORT 134 
#define  SLI4_READ_TOPOLOGY_SPEED_16G 133 
#define  SLI4_READ_TOPOLOGY_SPEED_1G 132 
#define  SLI4_READ_TOPOLOGY_SPEED_2G 131 
#define  SLI4_READ_TOPOLOGY_SPEED_32G 130 
#define  SLI4_READ_TOPOLOGY_SPEED_4G 129 
#define  SLI4_READ_TOPOLOGY_SPEED_8G 128 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_FC ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_DOWN ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_MAX ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_NO_ALPA ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_UP ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_LOOP ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_MAX ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_NPORT ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_read_fcf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 

__attribute__((used)) static int32_t
__ocs_read_topology_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	sli4_cmd_read_topology_t *read_topo = (sli4_cmd_read_topology_t *)mqe;

	if (status || read_topo->hdr.status) {
		ocs_log_debug(hw->os, "bad status cqe=%#x mqe=%#x\n",
				status, read_topo->hdr.status);
		ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
		return -1;
	}

	switch (read_topo->attention_type) {
	case SLI4_READ_TOPOLOGY_LINK_UP:
		hw->link.status = SLI_LINK_STATUS_UP;
		break;
	case SLI4_READ_TOPOLOGY_LINK_DOWN:
		hw->link.status = SLI_LINK_STATUS_DOWN;
		break;
	case SLI4_READ_TOPOLOGY_LINK_NO_ALPA:
		hw->link.status = SLI_LINK_STATUS_NO_ALPA;
		break;
	default:
		hw->link.status = SLI_LINK_STATUS_MAX;
		break;
	}

	switch (read_topo->topology) {
	case SLI4_READ_TOPOLOGY_NPORT:
		hw->link.topology = SLI_LINK_TOPO_NPORT;
		break;
	case SLI4_READ_TOPOLOGY_FC_AL:
		hw->link.topology = SLI_LINK_TOPO_LOOP;
		if (SLI_LINK_STATUS_UP == hw->link.status) {
			hw->link.loop_map = hw->loop_map.virt;
		}
		hw->link.fc_id = read_topo->acquired_al_pa;
		break;
	default:
		hw->link.topology = SLI_LINK_TOPO_MAX;
		break;
	}

	hw->link.medium = SLI_LINK_MEDIUM_FC;

	switch (read_topo->link_current.link_speed) {
	case SLI4_READ_TOPOLOGY_SPEED_1G:
		hw->link.speed =  1 * 1000;
		break;
	case SLI4_READ_TOPOLOGY_SPEED_2G:
		hw->link.speed =  2 * 1000;
		break;
	case SLI4_READ_TOPOLOGY_SPEED_4G:
		hw->link.speed =  4 * 1000;
		break;
	case SLI4_READ_TOPOLOGY_SPEED_8G:
		hw->link.speed =  8 * 1000;
		break;
	case SLI4_READ_TOPOLOGY_SPEED_16G:
		hw->link.speed = 16 * 1000;
		hw->link.loop_map = NULL;
		break;
	case SLI4_READ_TOPOLOGY_SPEED_32G:
		hw->link.speed = 32 * 1000;
		hw->link.loop_map = NULL;
		break;
	}

	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);

	ocs_hw_read_fcf(hw, SLI4_FCOE_FCF_TABLE_FIRST);

	return 0;
}