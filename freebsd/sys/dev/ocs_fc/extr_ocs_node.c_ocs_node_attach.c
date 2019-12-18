#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  hw; scalar_t__ enable_hlm; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_13__ {TYPE_4__* domain; } ;
typedef  TYPE_2__ ocs_sport_t ;
struct TYPE_14__ {int /*<<< orphan*/  sparm_dma_buf; int /*<<< orphan*/  rnode; scalar_t__ service_params; int /*<<< orphan*/  wwnn; int /*<<< orphan*/  wwpn; TYPE_1__* ocs; TYPE_2__* sport; } ;
typedef  TYPE_3__ ocs_node_t ;
struct TYPE_15__ {int /*<<< orphan*/  attached; } ;
typedef  TYPE_4__ ocs_domain_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ OCS_HW_RTN_IS_ERROR (int) ; 
 int /*<<< orphan*/  ocs_dma_copy_in (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int ocs_hw_node_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ocs_node_build_eui_name (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_node_get_wwnn (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_node_get_wwpn (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_node_group_init (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_node_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_node_unlock (TYPE_3__*) ; 

int32_t
ocs_node_attach(ocs_node_t *node)
{
	int32_t rc = 0;
	ocs_sport_t *sport = node->sport;
	ocs_domain_t *domain = sport->domain;
	ocs_t *ocs = node->ocs;

	if (!domain->attached) {
		ocs_log_test(ocs, "Warning: ocs_node_attach with unattached domain\n");
		return -1;
	}
	/* Update node->wwpn/wwnn */

	ocs_node_build_eui_name(node->wwpn, sizeof(node->wwpn), ocs_node_get_wwpn(node));
	ocs_node_build_eui_name(node->wwnn, sizeof(node->wwnn), ocs_node_get_wwnn(node));

	if (ocs->enable_hlm) {
		ocs_node_group_init(node);
	}

	ocs_dma_copy_in(&node->sparm_dma_buf, node->service_params+4, sizeof(node->service_params)-4);

	/* take lock to protect node->rnode.attached */
	ocs_node_lock(node);
		rc = ocs_hw_node_attach(&ocs->hw, &node->rnode, &node->sparm_dma_buf);
		if (OCS_HW_RTN_IS_ERROR(rc)) {
			ocs_log_test(ocs, "ocs_hw_node_attach failed: %d\n", rc);
		}
	ocs_node_unlock(node);

	return rc;
}