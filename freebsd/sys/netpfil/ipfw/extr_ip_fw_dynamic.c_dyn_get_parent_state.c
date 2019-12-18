#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ipfw_flow_id {int dummy; } ;
struct ip_fw {int rulenum; int /*<<< orphan*/  id; } ;
struct dyn_parent {int dummy; } ;
struct dyn_ipv6_state {struct dyn_parent* limit; } ;
struct dyn_ipv4_state {struct dyn_parent* limit; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 scalar_t__ DPARENT_COUNT (struct dyn_parent*) ; 
 int /*<<< orphan*/  DPARENT_COUNT_INC (struct dyn_parent*) ; 
 int /*<<< orphan*/  DYNSTATE_CRITICAL_ENTER () ; 
 int /*<<< orphan*/  DYNSTATE_CRITICAL_EXIT () ; 
 scalar_t__ DYN_BUCKET (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DYN_BUCKET_VERSION (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_IP4_FLOW_ID (struct ipfw_flow_id const*) ; 
 scalar_t__ IS_IP6_FLOW_ID (struct ipfw_flow_id const*) ; 
 int LOG_DEBUG ; 
 int LOG_SECURITY ; 
 int /*<<< orphan*/  O_LIMIT ; 
 int /*<<< orphan*/  V_curr_dyn_buckets ; 
 scalar_t__ V_fw_verbose ; 
 struct dyn_ipv4_state* dyn_add_ipv4_parent (struct ip_fw*,int /*<<< orphan*/ ,int,struct ipfw_flow_id const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dyn_ipv6_state* dyn_add_ipv6_parent (struct ip_fw*,int /*<<< orphan*/ ,int,struct ipfw_flow_id const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dyn_ipv4_state* dyn_lookup_ipv4_parent (struct ipfw_flow_id const*,struct ip_fw*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct dyn_ipv6_state* dyn_lookup_ipv6_parent (struct ipfw_flow_id const*,scalar_t__,struct ip_fw*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ipv4_parent_add ; 
 int /*<<< orphan*/  ipv6_parent_add ; 
 scalar_t__ last_log ; 
 int /*<<< orphan*/  print_dyn_rule_flags (struct ipfw_flow_id const*,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void *
dyn_get_parent_state(const struct ipfw_flow_id *pkt, uint32_t zoneid,
    struct ip_fw *rule, uint32_t hashval, uint32_t limit, uint16_t kidx)
{
	char sbuf[24];
	struct dyn_parent *p;
	void *ret;
	uint32_t bucket, version;

	p = NULL;
	ret = NULL;
	bucket = DYN_BUCKET(hashval, V_curr_dyn_buckets);
	DYNSTATE_CRITICAL_ENTER();
	if (IS_IP4_FLOW_ID(pkt)) {
		struct dyn_ipv4_state *s;

		version = DYN_BUCKET_VERSION(bucket, ipv4_parent_add);
		s = dyn_lookup_ipv4_parent(pkt, rule, rule->id,
		    rule->rulenum, bucket);
		if (s == NULL) {
			/*
			 * Exit from critical section because dyn_add_parent()
			 * will acquire bucket lock.
			 */
			DYNSTATE_CRITICAL_EXIT();

			s = dyn_add_ipv4_parent(rule, rule->id,
			    rule->rulenum, pkt, hashval, version, kidx);
			if (s == NULL)
				return (NULL);
			/* Now we are in critical section again. */
		}
		ret = s;
		p = s->limit;
	}
#ifdef INET6
	else if (IS_IP6_FLOW_ID(pkt)) {
		struct dyn_ipv6_state *s;

		version = DYN_BUCKET_VERSION(bucket, ipv6_parent_add);
		s = dyn_lookup_ipv6_parent(pkt, zoneid, rule, rule->id,
		    rule->rulenum, bucket);
		if (s == NULL) {
			/*
			 * Exit from critical section because dyn_add_parent()
			 * can acquire bucket mutex.
			 */
			DYNSTATE_CRITICAL_EXIT();

			s = dyn_add_ipv6_parent(rule, rule->id,
			    rule->rulenum, pkt, zoneid, hashval, version,
			    kidx);
			if (s == NULL)
				return (NULL);
			/* Now we are in critical section again. */
		}
		ret = s;
		p = s->limit;
	}
#endif
	else {
		DYNSTATE_CRITICAL_EXIT();
		return (NULL);
	}

	/* Check the limit */
	if (DPARENT_COUNT(p) >= limit) {
		DYNSTATE_CRITICAL_EXIT();
		if (V_fw_verbose && last_log != time_uptime) {
			last_log = time_uptime;
			snprintf(sbuf, sizeof(sbuf), "%u drop session",
			    rule->rulenum);
			print_dyn_rule_flags(pkt, O_LIMIT,
			    LOG_SECURITY | LOG_DEBUG, sbuf,
			    "too many entries");
		}
		return (NULL);
	}

	/* Take new session into account. */
	DPARENT_COUNT_INC(p);
	/*
	 * We must exit from critical section because the following code
	 * can acquire bucket mutex.
	 * We rely on the the 'count' field. The state will not expire
	 * until it has some child states, i.e. 'count' field is not zero.
	 * Return state pointer, it will be used by child states as parent.
	 */
	DYNSTATE_CRITICAL_EXIT();
	return (ret);
}