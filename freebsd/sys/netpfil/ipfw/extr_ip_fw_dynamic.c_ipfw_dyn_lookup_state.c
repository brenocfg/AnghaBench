#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ipfw_dyn_info {size_t f_pos; void* direction; int /*<<< orphan*/  hashval; int /*<<< orphan*/  kidx; } ;
struct ip_fw_args {int /*<<< orphan*/  f_id; } ;
struct ip_fw {scalar_t__ type; int set; TYPE_1__* limit; struct dyn_data* data; } ;
struct dyn_ipv6_state {scalar_t__ type; int set; TYPE_1__* limit; struct dyn_data* data; } ;
struct dyn_ipv4_state {scalar_t__ type; int set; TYPE_1__* limit; struct dyn_data* data; } ;
struct dyn_data {scalar_t__ chain_id; size_t f_pos; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  ruleid; struct ip_fw* parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  arg1; } ;
typedef  TYPE_2__ ipfw_insn ;
struct TYPE_9__ {scalar_t__ id; int n_rules; struct ip_fw** map; } ;
struct TYPE_7__ {struct ip_fw* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYNSTATE_CRITICAL_ENTER () ; 
 int /*<<< orphan*/  DYNSTATE_CRITICAL_EXIT () ; 
 int /*<<< orphan*/  DYN_DEBUG (char*,struct ip_fw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dyn_data*) ; 
 int /*<<< orphan*/  IPFW_RLOCK_ASSERT (TYPE_3__*) ; 
 scalar_t__ IS_IP4_FLOW_ID (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_IP6_FLOW_ID (int /*<<< orphan*/ *) ; 
 void* MATCH_NONE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ O_LIMIT ; 
 scalar_t__ V_dyn_keep_states ; 
 TYPE_3__ V_layer3_chain ; 
 int V_set_disable ; 
 int /*<<< orphan*/  dyn_getscopeid (struct ip_fw_args const*) ; 
 struct ip_fw* dyn_lookup_ipv4_state (int /*<<< orphan*/ *,void const*,struct ipfw_dyn_info*,int) ; 
 struct ip_fw* dyn_lookup_ipv6_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,struct ipfw_dyn_info*,int) ; 
 int /*<<< orphan*/  hash_packet (int /*<<< orphan*/ *) ; 
 size_t ipfw_find_rule (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ip_fw *
ipfw_dyn_lookup_state(const struct ip_fw_args *args, const void *ulp,
    int pktlen, const ipfw_insn *cmd, struct ipfw_dyn_info *info)
{
	struct dyn_data *data;
	struct ip_fw *rule;

	IPFW_RLOCK_ASSERT(&V_layer3_chain);

	data = NULL;
	rule = NULL;
	info->kidx = cmd->arg1;
	info->direction = MATCH_NONE;
	info->hashval = hash_packet(&args->f_id);

	DYNSTATE_CRITICAL_ENTER();
	if (IS_IP4_FLOW_ID(&args->f_id)) {
		struct dyn_ipv4_state *s;

		s = dyn_lookup_ipv4_state(&args->f_id, ulp, info, pktlen);
		if (s != NULL) {
			/*
			 * Dynamic states are created using the same 5-tuple,
			 * so it is assumed, that parent rule for O_LIMIT
			 * state has the same address family.
			 */
			data = s->data;
			if (s->type == O_LIMIT) {
				s = data->parent;
				rule = s->limit->parent;
			} else
				rule = data->parent;
		}
	}
#ifdef INET6
	else if (IS_IP6_FLOW_ID(&args->f_id)) {
		struct dyn_ipv6_state *s;

		s = dyn_lookup_ipv6_state(&args->f_id, dyn_getscopeid(args),
		    ulp, info, pktlen);
		if (s != NULL) {
			data = s->data;
			if (s->type == O_LIMIT) {
				s = data->parent;
				rule = s->limit->parent;
			} else
				rule = data->parent;
		}
	}
#endif
	if (data != NULL) {
		/*
		 * If cached chain id is the same, we can avoid rule index
		 * lookup. Otherwise do lookup and update chain_id and f_pos.
		 * It is safe even if there is concurrent thread that want
		 * update the same state, because chain->id can be changed
		 * only under IPFW_WLOCK().
		 */
		if (data->chain_id != V_layer3_chain.id) {
			data->f_pos = ipfw_find_rule(&V_layer3_chain,
			    data->rulenum, data->ruleid);
			/*
			 * Check that found state has not orphaned.
			 * When chain->id being changed the parent
			 * rule can be deleted. If found rule doesn't
			 * match the parent pointer, consider this
			 * result as MATCH_NONE and return NULL.
			 *
			 * This will lead to creation of new similar state
			 * that will be added into head of this bucket.
			 * And the state that we currently have matched
			 * should be deleted by dyn_expire_states().
			 *
			 * In case when dyn_keep_states is enabled, return
			 * pointer to deleted rule and f_pos value
			 * corresponding to penultimate rule.
			 * When we have enabled V_dyn_keep_states, states
			 * that become orphaned will get the DYN_REFERENCED
			 * flag and rule will keep around. So we can return
			 * it. But since it is not in the rules map, we need
			 * return such f_pos value, so after the state
			 * handling if the search will continue, the next rule
			 * will be the last one - the default rule.
			 */
			if (V_layer3_chain.map[data->f_pos] == rule) {
				data->chain_id = V_layer3_chain.id;
				info->f_pos = data->f_pos;
			} else if (V_dyn_keep_states != 0) {
				/*
				 * The original rule pointer is still usable.
				 * So, we return it, but f_pos need to be
				 * changed to point to the penultimate rule.
				 */
				MPASS(V_layer3_chain.n_rules > 1);
				data->chain_id = V_layer3_chain.id;
				data->f_pos = V_layer3_chain.n_rules - 2;
				info->f_pos = data->f_pos;
			} else {
				rule = NULL;
				info->direction = MATCH_NONE;
				DYN_DEBUG("rule %p  [%u, %u] is considered "
				    "invalid in data %p", rule, data->ruleid,
				    data->rulenum, data);
				/* info->f_pos doesn't matter here. */
			}
		} else
			info->f_pos = data->f_pos;
	}
	DYNSTATE_CRITICAL_EXIT();
#if 0
	/*
	 * Return MATCH_NONE if parent rule is in disabled set.
	 * This will lead to creation of new similar state that
	 * will be added into head of this bucket.
	 *
	 * XXXAE: we need to be able update state's set when parent
	 *	  rule set is changed.
	 */
	if (rule != NULL && (V_set_disable & (1 << rule->set))) {
		rule = NULL;
		info->direction = MATCH_NONE;
	}
#endif
	return (rule);
}