#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_27__ {int /*<<< orphan*/  sm_port_guid; TYPE_6__ opt; int /*<<< orphan*/  sm_base_lid; } ;
typedef  TYPE_9__ osm_subn_t ;
struct TYPE_23__ {int /*<<< orphan*/  mgid; } ;
struct TYPE_17__ {TYPE_5__ mcmember_rec; } ;
typedef  TYPE_10__ osm_mgrp_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_25__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  prefix; } ;
struct TYPE_26__ {TYPE_7__ unicast; } ;
struct TYPE_21__ {int /*<<< orphan*/  gid; } ;
struct TYPE_22__ {TYPE_3__ ntc_64_67; } ;
struct TYPE_19__ {int /*<<< orphan*/  trap_num; } ;
struct TYPE_20__ {TYPE_1__ generic; } ;
struct TYPE_18__ {int generic_type; TYPE_8__ issuer_gid; TYPE_4__ data_details; int /*<<< orphan*/  issuer_lid; TYPE_2__ g_or_v; } ;
typedef  TYPE_11__ ib_mad_notice_attr_t ;
typedef  int /*<<< orphan*/  ib_gid_t ;
typedef  int /*<<< orphan*/  ib_api_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_HTON16 (unsigned int) ; 
 int IB_NOTICE_TYPE_SUBN_MGMT ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  ib_get_err_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_notice_set_prod_type_ho (TYPE_11__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  osm_report_notice (int /*<<< orphan*/ *,TYPE_9__*,TYPE_11__*) ; 

__attribute__((used)) static void mgrp_send_notice(osm_subn_t * subn, osm_log_t * log,
			     osm_mgrp_t * mgrp, unsigned num)
{
	ib_mad_notice_attr_t notice;
	ib_api_status_t status;

	notice.generic_type = 0x80 | IB_NOTICE_TYPE_SUBN_MGMT;	/* is generic subn mgt type */
	ib_notice_set_prod_type_ho(&notice, 4);	/* A Class Manager generator */
	notice.g_or_v.generic.trap_num = CL_HTON16(num);
	/* The sm_base_lid is saved in network order already. */
	notice.issuer_lid = subn->sm_base_lid;
	/* following o14-12.1.11 and table 120 p726 */
	/* we need to provide the MGID */
	memcpy(&notice.data_details.ntc_64_67.gid,
	       &mgrp->mcmember_rec.mgid, sizeof(ib_gid_t));

	/* According to page 653 - the issuer gid in this case of trap
	   is the SM gid, since the SM is the initiator of this trap. */
	notice.issuer_gid.unicast.prefix = subn->opt.subnet_prefix;
	notice.issuer_gid.unicast.interface_id = subn->sm_port_guid;

	if ((status = osm_report_notice(log, subn, &notice)))
		OSM_LOG(log, OSM_LOG_ERROR, "ERR 7601: "
			"Error sending trap reports (%s)\n",
			ib_get_err_str(status));
}