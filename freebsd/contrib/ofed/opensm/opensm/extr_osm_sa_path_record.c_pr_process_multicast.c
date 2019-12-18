#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_21__ {int /*<<< orphan*/  p_log; int /*<<< orphan*/  p_subn; } ;
typedef  TYPE_3__ osm_sa_t ;
struct TYPE_18__ {int /*<<< orphan*/  raw; } ;
struct TYPE_24__ {int num_path; int mtu; int rate; int pkt_life; int hop_flow_raw; int /*<<< orphan*/  pkey; int /*<<< orphan*/  tclass; int /*<<< orphan*/  dlid; TYPE_11__ dgid; } ;
struct TYPE_20__ {TYPE_6__ path_rec; } ;
struct TYPE_22__ {int /*<<< orphan*/  list_item; TYPE_2__ resp; } ;
typedef  TYPE_4__ osm_sa_item_t ;
struct TYPE_19__ {int mtu; int rate; int pkt_life; TYPE_11__ mgid; int /*<<< orphan*/  sl_flow_hop; int /*<<< orphan*/  pkey; int /*<<< orphan*/  tclass; int /*<<< orphan*/  mlid; } ;
struct TYPE_23__ {TYPE_1__ mcmember_rec; } ;
typedef  TYPE_5__ osm_mgrp_t ;
typedef  int /*<<< orphan*/  ib_sa_mad_t ;
typedef  TYPE_6__ ib_path_rec_t ;
typedef  scalar_t__ ib_api_status_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;
typedef  int /*<<< orphan*/  cl_list_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IB_HOPLIMIT_MAX ; 
 scalar_t__ IB_MC_SCOPE_LINK_LOCAL ; 
 int IB_PATH_SELECTOR_EXACTLY ; 
 scalar_t__ IB_SUCCESS ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  SA_PR_RESP_SIZE ; 
 int cl_hton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_qlist_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_member_get_sl_flow_hop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_mgid_get_scope (TYPE_11__*) ; 
 int /*<<< orphan*/  ib_path_rec_set_qos_class (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_path_rec_set_sl (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ib_sa_mad_get_payload_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* osm_get_mgrp_by_mgid (int /*<<< orphan*/ ,TYPE_11__*) ; 
 scalar_t__ pr_match_mgrp_attributes (TYPE_3__*,int /*<<< orphan*/  const*,TYPE_5__*) ; 

__attribute__((used)) static void pr_process_multicast(osm_sa_t * sa, const ib_sa_mad_t *sa_mad,
				 cl_qlist_t *list)
{
	ib_path_rec_t *pr = ib_sa_mad_get_payload_ptr(sa_mad);
	osm_mgrp_t *mgrp;
	ib_api_status_t status;
	osm_sa_item_t *pr_item;
	uint32_t flow_label;
	uint8_t sl, hop_limit;

	OSM_LOG(sa->p_log, OSM_LOG_DEBUG, "Multicast destination requested\n");

	mgrp = osm_get_mgrp_by_mgid(sa->p_subn, &pr->dgid);
	if (!mgrp) {
		char gid_str[INET6_ADDRSTRLEN];
		OSM_LOG(sa->p_log, OSM_LOG_ERROR, "ERR 1F09: "
			"No MC group found for PathRecord destination GID %s\n",
			inet_ntop(AF_INET6, pr->dgid.raw, gid_str,
				  sizeof gid_str));
		return;
	}

	/* Make sure the rest of the PathRecord matches the MC group attributes */
	status = pr_match_mgrp_attributes(sa, sa_mad, mgrp);
	if (status != IB_SUCCESS) {
		OSM_LOG(sa->p_log, OSM_LOG_ERROR, "ERR 1F19: "
			"MC group attributes don't match PathRecord request\n");
		return;
	}

	pr_item = malloc(SA_PR_RESP_SIZE);
	if (pr_item == NULL) {
		OSM_LOG(sa->p_log, OSM_LOG_ERROR, "ERR 1F18: "
			"Unable to allocate path record for MC group\n");
		return;
	}
	memset(pr_item, 0, sizeof(cl_list_item_t));

	/* Copy PathRecord request into response */
	pr_item->resp.path_rec = *pr;

	/* Now, use the MC info to cruft up the PathRecord response */
	pr_item->resp.path_rec.dgid = mgrp->mcmember_rec.mgid;
	pr_item->resp.path_rec.dlid = mgrp->mcmember_rec.mlid;
	pr_item->resp.path_rec.tclass = mgrp->mcmember_rec.tclass;
	pr_item->resp.path_rec.num_path = 1;
	pr_item->resp.path_rec.pkey = mgrp->mcmember_rec.pkey;

	/* MTU, rate, and packet lifetime should be exactly */
	pr_item->resp.path_rec.mtu = (IB_PATH_SELECTOR_EXACTLY << 6) | mgrp->mcmember_rec.mtu;
	pr_item->resp.path_rec.rate = (IB_PATH_SELECTOR_EXACTLY << 6) | mgrp->mcmember_rec.rate;
	pr_item->resp.path_rec.pkt_life = (IB_PATH_SELECTOR_EXACTLY << 6) | mgrp->mcmember_rec.pkt_life;

	/* SL, Hop Limit, and Flow Label */
	ib_member_get_sl_flow_hop(mgrp->mcmember_rec.sl_flow_hop,
				  &sl, &flow_label, &hop_limit);
	ib_path_rec_set_sl(&pr_item->resp.path_rec, sl);
	ib_path_rec_set_qos_class(&pr_item->resp.path_rec, 0);

	/* HopLimit is not yet set in non link local MC groups */
	/* If it were, this would not be needed */
	if (ib_mgid_get_scope(&mgrp->mcmember_rec.mgid) !=
	    IB_MC_SCOPE_LINK_LOCAL)
		hop_limit = IB_HOPLIMIT_MAX;

	pr_item->resp.path_rec.hop_flow_raw =
	    cl_hton32(hop_limit) | (flow_label << 8);

	cl_qlist_insert_tail(list, &pr_item->list_item);
}