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
struct dyn_parent {int dummy; } ;
struct dyn_ipv4_state {struct dyn_parent* limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dyn_ipv4_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYNSTATE_CRITICAL_ENTER () ; 
 int /*<<< orphan*/  DYNSTATE_PROTECT (struct dyn_ipv4_state*) ; 
 scalar_t__ DYN_BUCKET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYN_BUCKET_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  DYN_BUCKET_UNLOCK (scalar_t__) ; 
 scalar_t__ DYN_BUCKET_VERSION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYN_BUCKET_VERSION_BUMP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYN_COUNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LIMIT_PARENT ; 
 int /*<<< orphan*/  V_curr_dyn_buckets ; 
 int /*<<< orphan*/ * V_dyn_ipv4_parent ; 
 int /*<<< orphan*/  V_dyn_parent_zone ; 
 struct dyn_ipv4_state* dyn_alloc_ipv4_state (struct ipfw_flow_id const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dyn_parent* dyn_alloc_parent (void*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dyn_ipv4_state* dyn_lookup_ipv4_parent_locked (struct ipfw_flow_id const*,void*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dyn_parent_count ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  ipv4_parent_add ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct dyn_parent*) ; 

__attribute__((used)) static struct dyn_ipv4_state *
dyn_add_ipv4_parent(void *rule, uint32_t ruleid, uint16_t rulenum,
    const struct ipfw_flow_id *pkt, uint32_t hashval, uint32_t version,
    uint16_t kidx)
{
	struct dyn_ipv4_state *s;
	struct dyn_parent *limit;
	uint32_t bucket;

	bucket = DYN_BUCKET(hashval, V_curr_dyn_buckets);
	DYN_BUCKET_LOCK(bucket);
	if (version != DYN_BUCKET_VERSION(bucket, ipv4_parent_add)) {
		/*
		 * Bucket version has been changed since last lookup,
		 * do lookup again to be sure that state does not exist.
		 */
		s = dyn_lookup_ipv4_parent_locked(pkt, rule, ruleid,
		    rulenum, bucket);
		if (s != NULL) {
			/*
			 * Simultaneous thread has already created this
			 * state. Just return it.
			 */
			DYNSTATE_CRITICAL_ENTER();
			DYNSTATE_PROTECT(s);
			DYN_BUCKET_UNLOCK(bucket);
			return (s);
		}
	}

	limit = dyn_alloc_parent(rule, ruleid, rulenum, hashval);
	if (limit == NULL) {
		DYN_BUCKET_UNLOCK(bucket);
		return (NULL);
	}

	s = dyn_alloc_ipv4_state(pkt, kidx, O_LIMIT_PARENT);
	if (s == NULL) {
		DYN_BUCKET_UNLOCK(bucket);
		uma_zfree(V_dyn_parent_zone, limit);
		return (NULL);
	}

	s->limit = limit;
	CK_SLIST_INSERT_HEAD(&V_dyn_ipv4_parent[bucket], s, entry);
	DYN_COUNT_INC(dyn_parent_count);
	DYN_BUCKET_VERSION_BUMP(bucket, ipv4_parent_add);
	DYNSTATE_CRITICAL_ENTER();
	DYNSTATE_PROTECT(s);
	DYN_BUCKET_UNLOCK(bucket);
	return (s);
}