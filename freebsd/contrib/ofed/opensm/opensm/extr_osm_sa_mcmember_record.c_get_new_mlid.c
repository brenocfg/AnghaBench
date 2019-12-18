#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  str ;
struct TYPE_11__ {scalar_t__ consolidate_ipv6_snm_req; } ;
struct TYPE_12__ {scalar_t__ max_mcast_lid_ho; int /*<<< orphan*/ * mboxes; TYPE_1__ opt; } ;
typedef  TYPE_2__ osm_subn_t ;
struct TYPE_13__ {TYPE_2__* p_subn; int /*<<< orphan*/  p_log; } ;
typedef  TYPE_3__ osm_sa_t ;
typedef  scalar_t__ ib_net16_t ;
struct TYPE_15__ {int /*<<< orphan*/  raw; } ;
struct TYPE_14__ {TYPE_6__ mgid; scalar_t__ mlid; } ;
typedef  TYPE_4__ ib_member_rec_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ IB_LID_MCAST_START_HO ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 scalar_t__ cl_hton16 (scalar_t__) ; 
 scalar_t__ cl_ntoh16 (scalar_t__) ; 
 scalar_t__ find_ipv6_snm_mlid (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ match_ipv6_snm_mgid (TYPE_6__*) ; 
 int /*<<< orphan*/  osm_get_mbox_by_mlid (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static ib_net16_t get_new_mlid(osm_sa_t * sa, ib_member_rec_t * mcmr)
{
	osm_subn_t *p_subn = sa->p_subn;
	ib_net16_t requested_mlid = mcmr->mlid;
	unsigned i, max;

	if (requested_mlid && cl_ntoh16(requested_mlid) >= IB_LID_MCAST_START_HO
	    && cl_ntoh16(requested_mlid) <= p_subn->max_mcast_lid_ho
	    && !osm_get_mbox_by_mlid(p_subn, requested_mlid))
		return requested_mlid;

	if (sa->p_subn->opt.consolidate_ipv6_snm_req
	    && match_ipv6_snm_mgid(&mcmr->mgid)
	    && (requested_mlid = find_ipv6_snm_mlid(sa->p_subn, &mcmr->mgid))) {
		char str[INET6_ADDRSTRLEN];
		OSM_LOG(sa->p_log, OSM_LOG_DEBUG,
			"Special Case Solicited Node Mcast Join for MGID %s\n",
			inet_ntop(AF_INET6, mcmr->mgid.raw, str, sizeof(str)));
		return requested_mlid;
	}

	max = p_subn->max_mcast_lid_ho - IB_LID_MCAST_START_HO + 1;
	for (i = 0; i < max; i++)
		if (!sa->p_subn->mboxes[i])
			return cl_hton16(i + IB_LID_MCAST_START_HO);

	return 0;
}