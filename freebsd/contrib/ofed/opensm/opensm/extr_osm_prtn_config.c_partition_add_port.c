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
struct part_conf {scalar_t__ membership; int /*<<< orphan*/  indx0; TYPE_2__* p_subn; int /*<<< orphan*/  p_log; int /*<<< orphan*/ * p_prtn; } ;
typedef  int /*<<< orphan*/  osm_prtn_t ;
typedef  scalar_t__ membership_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;
struct TYPE_3__ {scalar_t__ allow_both_pkeys; } ;
struct TYPE_4__ {TYPE_1__ opt; int /*<<< orphan*/  sm_port_guid; } ;

/* Variables and functions */
 scalar_t__ BOTH ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FULL ; 
 int /*<<< orphan*/  IB_NODE_TYPE_CA ; 
 int /*<<< orphan*/  IB_NODE_TYPE_ROUTER ; 
 int /*<<< orphan*/  IB_NODE_TYPE_SWITCH ; 
 scalar_t__ IB_SUCCESS ; 
 scalar_t__ LIMITED ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cl_hton64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_ntoh64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manage_membership_change (struct part_conf*,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ osm_prtn_add_port (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int partition_add_all (struct part_conf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int partition_add_port(unsigned lineno, struct part_conf *conf,
			      char *name, char *flag)
{
	osm_prtn_t *p = conf->p_prtn;
	ib_net64_t guid;
	membership_t membership = conf->membership;

	if (!name || !*name || !strncmp(name, "NONE", strlen(name)))
		return 0;

	if (flag) {
		/* reset default membership to limited */
		membership = LIMITED;
		if (!strncmp(flag, "full", strlen(flag)))
			membership = FULL;
		else if (!strncmp(flag, "both", strlen(flag)))
			membership = BOTH;
		else if (strncmp(flag, "limited", strlen(flag))) {
			OSM_LOG(conf->p_log, OSM_LOG_VERBOSE,
				"PARSE WARN: line %d: "
				"unrecognized port flag \'%s\'."
				" Assume \'limited\'\n", lineno, flag);
		}
	}

	if (!strncmp(name, "ALL", strlen(name)))
		return partition_add_all(conf, p, 0, membership);
	else if (!strncmp(name, "ALL_CAS", strlen(name)))
		return partition_add_all(conf, p, IB_NODE_TYPE_CA, membership);
	else if (!strncmp(name, "ALL_SWITCHES", strlen(name)))
		return partition_add_all(conf, p, IB_NODE_TYPE_SWITCH,
					 membership);
	else if (!strncmp(name, "ALL_ROUTERS", strlen(name)))
		return partition_add_all(conf, p, IB_NODE_TYPE_ROUTER,
					 membership);
	else if (!strncmp(name, "SELF", strlen(name))) {
		guid = cl_ntoh64(conf->p_subn->sm_port_guid);
	} else {
		char *end;
		guid = strtoull(name, &end, 0);
		if (!guid || *end)
			return -1;
	}

	manage_membership_change(conf, p, 0xFF, membership, guid);
	if (membership != LIMITED &&
	    osm_prtn_add_port(conf->p_log, conf->p_subn, p,
			      cl_hton64(guid), TRUE, conf->indx0) != IB_SUCCESS)
		return -1;
	if ((membership == LIMITED ||
	    (membership == BOTH && conf->p_subn->opt.allow_both_pkeys)) &&
	    osm_prtn_add_port(conf->p_log, conf->p_subn, p,
			      cl_hton64(guid), FALSE, conf->indx0) != IB_SUCCESS)
		return -1;
	return 0;
}