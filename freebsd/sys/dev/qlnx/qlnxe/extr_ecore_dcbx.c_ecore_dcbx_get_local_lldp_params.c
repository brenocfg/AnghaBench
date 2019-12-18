#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lldp_config_params_s {int /*<<< orphan*/  local_port_id; int /*<<< orphan*/  local_chassis_id; } ;
struct ecore_hwfn {TYPE_1__* p_dcbx_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_port_id; int /*<<< orphan*/  local_chassis_id; } ;
struct ecore_dcbx_get {TYPE_2__ lldp_local; } ;
struct TYPE_3__ {struct lldp_config_params_s* lldp_local; } ;

/* Variables and functions */
 size_t LLDP_NEAREST_BRIDGE ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_dcbx_get_local_lldp_params(struct ecore_hwfn *p_hwfn,
					     struct ecore_dcbx_get *params)
{
	struct lldp_config_params_s *p_local;

	p_local = &p_hwfn->p_dcbx_info->lldp_local[LLDP_NEAREST_BRIDGE];

	OSAL_MEMCPY(params->lldp_local.local_chassis_id,
		    p_local->local_chassis_id,
		    sizeof(params->lldp_local.local_chassis_id));
	OSAL_MEMCPY(params->lldp_local.local_port_id, p_local->local_port_id,
		    sizeof(params->lldp_local.local_port_id));
}