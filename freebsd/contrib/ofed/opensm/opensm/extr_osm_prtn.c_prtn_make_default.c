#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sm_port_guid; } ;
typedef  TYPE_1__ osm_subn_t ;
struct TYPE_13__ {int /*<<< orphan*/  part_guid_tbl; } ;
typedef  TYPE_2__ osm_prtn_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  scalar_t__ ib_api_status_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IB_DEFAULT_PARTIAL_PKEY ; 
 scalar_t__ IB_SUCCESS ; 
 scalar_t__ IB_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  OSM_DEFAULT_MGRP_MTU ; 
 int /*<<< orphan*/  OSM_DEFAULT_MGRP_RATE ; 
 int /*<<< orphan*/  OSM_DEFAULT_SL ; 
 int /*<<< orphan*/  OSM_IPOIB_BROADCAST_MGRP_QKEY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cl_map_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_ipoib_broadcast_mgid ; 
 scalar_t__ osm_prtn_add_all (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_prtn_add_mcgroup (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ osm_prtn_add_port (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* osm_prtn_make_new (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ib_api_status_t prtn_make_default(osm_log_t * p_log, osm_subn_t * p_subn,
					 boolean_t no_config)
{
	ib_api_status_t status = IB_UNKNOWN_ERROR;
	osm_prtn_t *p;

	p = osm_prtn_make_new(p_log, p_subn, "Default",
			      IB_DEFAULT_PARTIAL_PKEY);
	if (!p)
		goto _err;
	status = osm_prtn_add_all(p_log, p_subn, p, 0, no_config, FALSE);
	if (status != IB_SUCCESS)
		goto _err;
	cl_map_remove(&p->part_guid_tbl, p_subn->sm_port_guid);
	status =
	    osm_prtn_add_port(p_log, p_subn, p, p_subn->sm_port_guid, TRUE, FALSE);

	/* ipv4 broadcast group */
	if (no_config)
		osm_prtn_add_mcgroup(p_log, p_subn, p, OSM_DEFAULT_MGRP_RATE,
				     OSM_DEFAULT_MGRP_MTU, OSM_DEFAULT_SL,
				     0, OSM_IPOIB_BROADCAST_MGRP_QKEY, 0, 0,
				     &osm_ipoib_broadcast_mgid);

_err:
	return status;
}