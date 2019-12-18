#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fc_id; int /*<<< orphan*/ * loop_map; scalar_t__ speed; int /*<<< orphan*/  medium; int /*<<< orphan*/  topology; int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_1__ link; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_MAX ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_MAX ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_NONE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  ocs_hw_assert (TYPE_2__*) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_link_event_init(ocs_hw_t *hw)
{
	ocs_hw_assert(hw);

	hw->link.status = SLI_LINK_STATUS_MAX;
	hw->link.topology = SLI_LINK_TOPO_NONE;
	hw->link.medium = SLI_LINK_MEDIUM_MAX;
	hw->link.speed = 0;
	hw->link.loop_map = NULL;
	hw->link.fc_id = UINT32_MAX;

	return OCS_HW_RTN_SUCCESS;
}