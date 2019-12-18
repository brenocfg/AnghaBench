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
typedef  int /*<<< orphan*/  osm_qos_vlarb_scope_t ;
typedef  int /*<<< orphan*/  osm_qos_sl2vl_scope_t ;
typedef  int /*<<< orphan*/  osm_qos_port_group_t ;
struct TYPE_4__ {scalar_t__ p_node_hash; int /*<<< orphan*/  qos_match_rules; int /*<<< orphan*/  qos_levels; int /*<<< orphan*/  sl2vl_tables; int /*<<< orphan*/  vlarb_tables; int /*<<< orphan*/  port_groups; } ;
typedef  TYPE_1__ osm_qos_policy_t ;
typedef  int /*<<< orphan*/  osm_qos_match_rule_t ;
typedef  int /*<<< orphan*/  osm_qos_level_t ;
typedef  scalar_t__ cl_list_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_list_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_list_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_list_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_list_next (scalar_t__) ; 
 scalar_t__ cl_list_obj (scalar_t__) ; 
 int /*<<< orphan*/  cl_list_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  osm_qos_policy_match_rule_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_qos_policy_port_group_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_qos_policy_qos_level_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_qos_policy_sl2vl_scope_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_qos_policy_vlarb_scope_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_free_table (scalar_t__) ; 

void osm_qos_policy_destroy(osm_qos_policy_t * p_qos_policy)
{
	cl_list_iterator_t list_iterator;
	osm_qos_port_group_t *p_port_group = NULL;
	osm_qos_vlarb_scope_t *p_vlarb_scope = NULL;
	osm_qos_sl2vl_scope_t *p_sl2vl_scope = NULL;
	osm_qos_level_t *p_qos_level = NULL;
	osm_qos_match_rule_t *p_qos_match_rule = NULL;

	if (!p_qos_policy)
		return;

	list_iterator = cl_list_head(&p_qos_policy->port_groups);
	while (list_iterator != cl_list_end(&p_qos_policy->port_groups)) {
		p_port_group =
		    (osm_qos_port_group_t *) cl_list_obj(list_iterator);
		if (p_port_group)
			osm_qos_policy_port_group_destroy(p_port_group);
		list_iterator = cl_list_next(list_iterator);
	}
	cl_list_remove_all(&p_qos_policy->port_groups);
	cl_list_destroy(&p_qos_policy->port_groups);

	list_iterator = cl_list_head(&p_qos_policy->vlarb_tables);
	while (list_iterator != cl_list_end(&p_qos_policy->vlarb_tables)) {
		p_vlarb_scope =
		    (osm_qos_vlarb_scope_t *) cl_list_obj(list_iterator);
		if (p_vlarb_scope)
			osm_qos_policy_vlarb_scope_destroy(p_vlarb_scope);
		list_iterator = cl_list_next(list_iterator);
	}
	cl_list_remove_all(&p_qos_policy->vlarb_tables);
	cl_list_destroy(&p_qos_policy->vlarb_tables);

	list_iterator = cl_list_head(&p_qos_policy->sl2vl_tables);
	while (list_iterator != cl_list_end(&p_qos_policy->sl2vl_tables)) {
		p_sl2vl_scope =
		    (osm_qos_sl2vl_scope_t *) cl_list_obj(list_iterator);
		if (p_sl2vl_scope)
			osm_qos_policy_sl2vl_scope_destroy(p_sl2vl_scope);
		list_iterator = cl_list_next(list_iterator);
	}
	cl_list_remove_all(&p_qos_policy->sl2vl_tables);
	cl_list_destroy(&p_qos_policy->sl2vl_tables);

	list_iterator = cl_list_head(&p_qos_policy->qos_levels);
	while (list_iterator != cl_list_end(&p_qos_policy->qos_levels)) {
		p_qos_level = (osm_qos_level_t *) cl_list_obj(list_iterator);
		if (p_qos_level)
			osm_qos_policy_qos_level_destroy(p_qos_level);
		list_iterator = cl_list_next(list_iterator);
	}
	cl_list_remove_all(&p_qos_policy->qos_levels);
	cl_list_destroy(&p_qos_policy->qos_levels);

	list_iterator = cl_list_head(&p_qos_policy->qos_match_rules);
	while (list_iterator != cl_list_end(&p_qos_policy->qos_match_rules)) {
		p_qos_match_rule =
		    (osm_qos_match_rule_t *) cl_list_obj(list_iterator);
		if (p_qos_match_rule)
			osm_qos_policy_match_rule_destroy(p_qos_match_rule);
		list_iterator = cl_list_next(list_iterator);
	}
	cl_list_remove_all(&p_qos_policy->qos_match_rules);
	cl_list_destroy(&p_qos_policy->qos_match_rules);

	if (p_qos_policy->p_node_hash)
		st_free_table(p_qos_policy->p_node_hash);

	free(p_qos_policy);

	p_qos_policy = NULL;
}