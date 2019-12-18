#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  qos_match_rules; TYPE_2__* p_subn; } ;
typedef  TYPE_3__ osm_qos_policy_t ;
struct TYPE_11__ {char* use; scalar_t__ pkey_range_len; int /*<<< orphan*/  pkey_range_arr; scalar_t__ service_id_range_len; int /*<<< orphan*/  service_id_range_arr; scalar_t__ qos_class_range_len; int /*<<< orphan*/  qos_class_range_arr; int /*<<< orphan*/  destination_group_list; int /*<<< orphan*/  source_group_list; } ;
typedef  TYPE_4__ osm_qos_match_rule_t ;
typedef  int /*<<< orphan*/  osm_physp_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  int ib_net64_t ;
typedef  scalar_t__ cl_list_iterator_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {TYPE_1__* p_osm; } ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int IB_PR_COMPMASK_PKEY ; 
 int IB_PR_COMPMASK_QOS_CLASS ; 
 int IB_PR_COMPMASK_SERVICEID_LSB ; 
 int IB_PR_COMPMASK_SERVICEID_MSB ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  __is_num_in_range_arr (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ __qos_policy_is_port_in_group_list (TYPE_3__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ cl_list_count (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_list_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_list_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_list_next (scalar_t__) ; 
 scalar_t__ cl_list_obj (scalar_t__) ; 

__attribute__((used)) static osm_qos_match_rule_t *__qos_policy_get_match_rule_by_params(
			 const osm_qos_policy_t * p_qos_policy,
			 uint64_t service_id,
			 uint16_t qos_class,
			 uint16_t pkey,
			 const osm_physp_t * p_src_physp,
			 const osm_physp_t * p_dest_physp,
			 ib_net64_t comp_mask)
{
	osm_qos_match_rule_t *p_qos_match_rule = NULL;
	cl_list_iterator_t list_iterator;
	osm_log_t * p_log = &p_qos_policy->p_subn->p_osm->log;

	boolean_t matched_by_sguid = FALSE,
		  matched_by_dguid = FALSE,
		  matched_by_sordguid = FALSE,
		  matched_by_class = FALSE,
		  matched_by_sid = FALSE,
		  matched_by_pkey = FALSE;

	if (!cl_list_count(&p_qos_policy->qos_match_rules))
		return NULL;

	OSM_LOG_ENTER(p_log);

	/* Go over all QoS match rules and find the one that matches the request */

	list_iterator = cl_list_head(&p_qos_policy->qos_match_rules);
	while (list_iterator != cl_list_end(&p_qos_policy->qos_match_rules)) {
		p_qos_match_rule =
		    (osm_qos_match_rule_t *) cl_list_obj(list_iterator);
		if (!p_qos_match_rule) {
			list_iterator = cl_list_next(list_iterator);
			continue;
		}

		/* If a match rule has Source groups and no Destination groups,
		 * PR request source has to be in this list */

		if (cl_list_count(&p_qos_match_rule->source_group_list)
		    && !cl_list_count(&p_qos_match_rule->destination_group_list)) {
			if (!__qos_policy_is_port_in_group_list(p_qos_policy,
								p_src_physp,
								&p_qos_match_rule->
								source_group_list))
			{
				list_iterator = cl_list_next(list_iterator);
				continue;
			}
			matched_by_sguid = TRUE;
		}

		/* If a match rule has Destination groups and no Source groups,
		 * PR request dest. has to be in this list */

		if (cl_list_count(&p_qos_match_rule->destination_group_list)
		    && !cl_list_count(&p_qos_match_rule->source_group_list)) {
			if (!__qos_policy_is_port_in_group_list(p_qos_policy,
								p_dest_physp,
								&p_qos_match_rule->
								destination_group_list))
			{
				list_iterator = cl_list_next(list_iterator);
				continue;
			}
			matched_by_dguid = TRUE;
		}

		/* If a match rule has both Source and Destination groups,
		 * PR request source or dest. must be in respective list
		 */
		if (cl_list_count(&p_qos_match_rule->source_group_list)
		    && cl_list_count(&p_qos_match_rule->destination_group_list)) {
			if (__qos_policy_is_port_in_group_list(p_qos_policy,
							       p_src_physp,
							       &p_qos_match_rule->
							       source_group_list)
			    && __qos_policy_is_port_in_group_list(p_qos_policy,
								  p_dest_physp,
								  &p_qos_match_rule->
								  destination_group_list))
				matched_by_sordguid = TRUE;
			else {
				list_iterator = cl_list_next(list_iterator);
				continue;
			}
		}

		/* If a match rule has QoS classes, PR request HAS
		   to have a matching QoS class to match the rule */

		if (p_qos_match_rule->qos_class_range_len) {
			if (!(comp_mask & IB_PR_COMPMASK_QOS_CLASS)) {
				list_iterator = cl_list_next(list_iterator);
				continue;
			}

			if (!__is_num_in_range_arr
			    (p_qos_match_rule->qos_class_range_arr,
			     p_qos_match_rule->qos_class_range_len,
			     qos_class)) {
				list_iterator = cl_list_next(list_iterator);
				continue;
			}
			matched_by_class = TRUE;
		}

		/* If a match rule has Service IDs, PR request HAS
		   to have a matching Service ID to match the rule */

		if (p_qos_match_rule->service_id_range_len) {
			if (!(comp_mask & IB_PR_COMPMASK_SERVICEID_MSB) ||
			    !(comp_mask & IB_PR_COMPMASK_SERVICEID_LSB)) {
				list_iterator = cl_list_next(list_iterator);
				continue;
			}

			if (!__is_num_in_range_arr
			    (p_qos_match_rule->service_id_range_arr,
			     p_qos_match_rule->service_id_range_len,
			     service_id)) {
				list_iterator = cl_list_next(list_iterator);
				continue;
			}
			matched_by_sid = TRUE;
		}

		/* If a match rule has PKeys, PR request HAS
		   to have a matching PKey to match the rule */

		if (p_qos_match_rule->pkey_range_len) {
			if (!(comp_mask & IB_PR_COMPMASK_PKEY)) {
				list_iterator = cl_list_next(list_iterator);
				continue;
			}

			if (!__is_num_in_range_arr
			    (p_qos_match_rule->pkey_range_arr,
			     p_qos_match_rule->pkey_range_len,
			     pkey & 0x7FFF)) {
				list_iterator = cl_list_next(list_iterator);
				continue;
			}
			matched_by_pkey = TRUE;
		}

		/* if we got here, then this match-rule matched this PR request */
		break;
	}

	if (list_iterator == cl_list_end(&p_qos_policy->qos_match_rules))
		p_qos_match_rule = NULL;

	if (p_qos_match_rule)
		OSM_LOG(p_log, OSM_LOG_DEBUG,
			"request matched rule (%s) by:%s%s%s%s%s%s\n",
			(p_qos_match_rule->use) ?
				p_qos_match_rule->use : "no description",
			(matched_by_sguid) ? " SGUID" : "",
			(matched_by_dguid) ? " DGUID" : "",
			(matched_by_sordguid) ? "SorDGUID" : "",
			(matched_by_class) ? " QoS_Class" : "",
			(matched_by_sid)   ? " ServiceID" : "",
			(matched_by_pkey)  ? " PKey" : "");
	else
		OSM_LOG(p_log, OSM_LOG_DEBUG,
			"request not matched any rule\n");

	OSM_LOG_EXIT(p_log);
	return p_qos_match_rule;
}