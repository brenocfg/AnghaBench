#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  p_log; int /*<<< orphan*/  p_subn; } ;
typedef  TYPE_3__ osm_sm_t ;
struct TYPE_14__ {int /*<<< orphan*/  guid; } ;
struct TYPE_17__ {TYPE_1__ smi; } ;
typedef  TYPE_4__ osm_remote_sm_t ;
struct TYPE_18__ {TYPE_10__* p_physp; } ;
typedef  TYPE_5__ osm_port_t ;
struct TYPE_15__ {int /*<<< orphan*/  light_sweep; int /*<<< orphan*/  set_method; int /*<<< orphan*/  port_guid; } ;
struct TYPE_19__ {TYPE_2__ smi_context; } ;
typedef  TYPE_6__ osm_madw_context_t ;
typedef  scalar_t__ ib_api_status_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;
struct TYPE_13__ {int /*<<< orphan*/  port_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_DISP_MSGID_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IB_MAD_ATTR_SM_INFO ; 
 scalar_t__ IB_SUCCESS ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* cl_item_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_get_err_str (scalar_t__) ; 
 int /*<<< orphan*/  ib_port_info_get_m_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_item ; 
 TYPE_5__* osm_get_port_by_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_physp_get_dr_path_ptr (TYPE_10__*) ; 
 scalar_t__ osm_req_get (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_4__* r_sm ; 

__attribute__((used)) static void query_sm_info(cl_map_item_t * item, void *cxt)
{
	osm_madw_context_t context;
	osm_remote_sm_t *r_sm = cl_item_obj(item, r_sm, map_item);
	osm_sm_t *sm = cxt;
	ib_api_status_t ret;
	osm_port_t *p_port;

	p_port= osm_get_port_by_guid(sm->p_subn, r_sm->smi.guid);
	if (p_port == NULL) {
		OSM_LOG(sm->p_log, OSM_LOG_ERROR, "ERR 3340: "
			"No port object on given sm object\n");
		return;
        }

	context.smi_context.port_guid = r_sm->smi.guid;
	context.smi_context.set_method = FALSE;
	context.smi_context.light_sweep = TRUE;

	ret = osm_req_get(sm, osm_physp_get_dr_path_ptr(p_port->p_physp),
			  IB_MAD_ATTR_SM_INFO, 0, FALSE,
			  ib_port_info_get_m_key(&p_port->p_physp->port_info),
			  CL_DISP_MSGID_NONE, &context);
	if (ret != IB_SUCCESS)
		OSM_LOG(sm->p_log, OSM_LOG_ERROR, "ERR 3314: "
			"Failure requesting SMInfo (%s)\n",
			ib_get_err_str(ret));
}