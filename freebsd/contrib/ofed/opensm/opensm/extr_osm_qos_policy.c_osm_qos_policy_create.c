#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_subn_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_subn; int /*<<< orphan*/  qos_match_rules; int /*<<< orphan*/  qos_levels; int /*<<< orphan*/  sl2vl_tables; int /*<<< orphan*/  vlarb_tables; int /*<<< orphan*/  port_groups; } ;
typedef  TYPE_1__ osm_qos_policy_t ;

/* Variables and functions */
 int /*<<< orphan*/  __build_nodebyname_hash (TYPE_1__*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cl_list_construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_list_init (int /*<<< orphan*/ *,int) ; 

osm_qos_policy_t * osm_qos_policy_create(osm_subn_t * p_subn)
{
	osm_qos_policy_t * p_qos_policy = (osm_qos_policy_t *)calloc(1, sizeof(osm_qos_policy_t));
	if (!p_qos_policy)
		return NULL;

	cl_list_construct(&p_qos_policy->port_groups);
	cl_list_init(&p_qos_policy->port_groups, 10);

	cl_list_construct(&p_qos_policy->vlarb_tables);
	cl_list_init(&p_qos_policy->vlarb_tables, 10);

	cl_list_construct(&p_qos_policy->sl2vl_tables);
	cl_list_init(&p_qos_policy->sl2vl_tables, 10);

	cl_list_construct(&p_qos_policy->qos_levels);
	cl_list_init(&p_qos_policy->qos_levels, 10);

	cl_list_construct(&p_qos_policy->qos_match_rules);
	cl_list_init(&p_qos_policy->qos_match_rules, 10);

	p_qos_policy->p_subn = p_subn;
	__build_nodebyname_hash(p_qos_policy);

	return p_qos_policy;
}