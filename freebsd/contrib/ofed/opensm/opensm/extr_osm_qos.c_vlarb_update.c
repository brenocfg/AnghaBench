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
typedef  int /*<<< orphan*/  uint8_t ;
struct qos_config {int /*<<< orphan*/ * vlarb_high; int /*<<< orphan*/ * vlarb_low; } ;
typedef  int /*<<< orphan*/  osm_sm_t ;
struct TYPE_6__ {unsigned int vl_arb_low_cap; unsigned int vl_arb_high_cap; } ;
struct TYPE_5__ {TYPE_2__ port_info; } ;
typedef  TYPE_1__ osm_physp_t ;
typedef  TYPE_2__ ib_port_info_t ;
typedef  int /*<<< orphan*/  ib_api_status_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;

/* Variables and functions */
 unsigned int IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK ; 
 int /*<<< orphan*/  IB_SUCCESS ; 
 int /*<<< orphan*/  vlarb_update_table_block (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ib_api_status_t vlarb_update(osm_sm_t * sm, osm_physp_t * p,
				    uint8_t port_num, unsigned force_update,
				    const struct qos_config *qcfg,
				    cl_qlist_t *mad_list)
{
	ib_api_status_t status = IB_SUCCESS;
	ib_port_info_t *p_pi = &p->port_info;
	unsigned len;

	if (p_pi->vl_arb_low_cap > 0) {
		len = p_pi->vl_arb_low_cap < IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK ?
		    p_pi->vl_arb_low_cap : IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK;
		if ((status = vlarb_update_table_block(sm, p, port_num,
						       force_update,
						       &qcfg->vlarb_low[0],
						       len, 0,
						       mad_list)) != IB_SUCCESS)
			return status;
	}
	if (p_pi->vl_arb_low_cap > IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK) {
		len = p_pi->vl_arb_low_cap % IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK;
		if ((status = vlarb_update_table_block(sm, p, port_num,
						       force_update,
						       &qcfg->vlarb_low[1],
						       len, 1,
						       mad_list)) != IB_SUCCESS)
			return status;
	}
	if (p_pi->vl_arb_high_cap > 0) {
		len = p_pi->vl_arb_high_cap < IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK ?
		    p_pi->vl_arb_high_cap : IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK;
		if ((status = vlarb_update_table_block(sm, p, port_num,
						       force_update,
						       &qcfg->vlarb_high[0],
						       len, 2,
						       mad_list)) != IB_SUCCESS)
			return status;
	}
	if (p_pi->vl_arb_high_cap > IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK) {
		len = p_pi->vl_arb_high_cap % IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK;
		if ((status = vlarb_update_table_block(sm, p, port_num,
						       force_update,
						       &qcfg->vlarb_high[1],
						       len, 3,
						       mad_list)) != IB_SUCCESS)
			return status;
	}

	return status;
}