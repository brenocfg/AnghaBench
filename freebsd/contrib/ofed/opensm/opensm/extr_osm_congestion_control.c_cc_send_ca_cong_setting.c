#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  p_log; TYPE_2__* p_subn; } ;
typedef  TYPE_5__ osm_sm_t ;
struct TYPE_14__ {int /*<<< orphan*/  ca_cong_setting; } ;
struct TYPE_15__ {TYPE_3__ ca; } ;
struct TYPE_17__ {TYPE_4__ cc; scalar_t__ need_update; } ;
typedef  TYPE_6__ osm_physp_t ;
typedef  int /*<<< orphan*/  osm_node_t ;
typedef  int /*<<< orphan*/  osm_madw_t ;
struct TYPE_18__ {int /*<<< orphan*/  ca_cong_setting; int /*<<< orphan*/  bind_handle; int /*<<< orphan*/  mad_pool; } ;
typedef  TYPE_7__ osm_congestion_control_t ;
typedef  int /*<<< orphan*/  ib_cc_mad_t ;
typedef  int /*<<< orphan*/  ib_ca_cong_setting_t ;
typedef  int /*<<< orphan*/  ib_api_status_t ;
struct TYPE_13__ {scalar_t__ need_update; TYPE_1__* p_osm; } ;
struct TYPE_12__ {TYPE_7__ cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_INSUFFICIENT_MEMORY ; 
 int /*<<< orphan*/  IB_MAD_ATTR_CA_CONG_SETTING ; 
 int /*<<< orphan*/  IB_SUCCESS ; 
 int /*<<< orphan*/  MAD_BLOCK_SIZE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_mad_post (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ib_cc_mad_get_mgt_data_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * osm_mad_pool_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * osm_madw_get_cc_mad_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ib_api_status_t cc_send_ca_cong_setting(osm_sm_t * p_sm,
					       osm_node_t *p_node,
					       osm_physp_t *p_physp)
{
	osm_congestion_control_t *p_cc = &p_sm->p_subn->p_osm->cc;
	unsigned force_update;
	osm_madw_t *p_madw = NULL;
	ib_cc_mad_t *p_cc_mad = NULL;
	ib_ca_cong_setting_t *p_ca_cong_setting = NULL;

	OSM_LOG_ENTER(p_sm->p_log);

	force_update = p_physp->need_update || p_sm->p_subn->need_update;

	if (!force_update
	    && !memcmp(&p_cc->ca_cong_setting,
		       &p_physp->cc.ca.ca_cong_setting,
		       sizeof(p_cc->ca_cong_setting)))
		return IB_SUCCESS;

	p_madw = osm_mad_pool_get(p_cc->mad_pool, p_cc->bind_handle,
				  MAD_BLOCK_SIZE, NULL);
	if (p_madw == NULL) {
		OSM_LOG(p_sm->p_log, OSM_LOG_ERROR, "ERR C102: "
			"failed to allocate mad\n");
		return IB_INSUFFICIENT_MEMORY;
	}

	p_cc_mad = osm_madw_get_cc_mad_ptr(p_madw);

	p_ca_cong_setting = ib_cc_mad_get_mgt_data_ptr(p_cc_mad);

	memcpy(p_ca_cong_setting,
	       &p_cc->ca_cong_setting,
	       sizeof(p_cc->ca_cong_setting));

	cc_mad_post(p_cc, p_madw, p_node, p_physp,
		    IB_MAD_ATTR_CA_CONG_SETTING, 0);

	OSM_LOG_EXIT(p_sm->p_log);

	return IB_SUCCESS;
}