#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_7__ {int /*<<< orphan*/  dname_len; int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; } ;
struct TYPE_6__ {struct trust_anchor* key; } ;
struct trust_anchor {TYPE_4__* autr; int /*<<< orphan*/  lock; int /*<<< orphan*/  dclass; int /*<<< orphan*/  name; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  namelen; TYPE_1__ node; } ;
struct module_env {scalar_t__* now; TYPE_5__* anchors; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_3__* autr; int /*<<< orphan*/  tree; } ;
struct TYPE_9__ {scalar_t__ next_probe_time; int /*<<< orphan*/  pnode; int /*<<< orphan*/  query_interval; } ;
struct TYPE_8__ {int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ calc_next_probe (struct module_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,struct trust_anchor*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ ,struct trust_anchor*) ; 
 int /*<<< orphan*/  reset_worker_timer (struct module_env*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wait_probe_time (TYPE_5__*) ; 

__attribute__((used)) static int
set_next_probe(struct module_env* env, struct trust_anchor* tp,
	struct ub_packed_rrset_key* dnskey_rrset)
{
	struct trust_anchor key, *tp2;
	time_t mold, mnew;
	/* use memory allocated in rrset for temporary name storage */
	key.node.key = &key;
	key.name = dnskey_rrset->rk.dname;
	key.namelen = dnskey_rrset->rk.dname_len;
	key.namelabs = dname_count_labels(key.name);
	key.dclass = tp->dclass;
	lock_basic_unlock(&tp->lock);

	/* fetch tp again and lock anchors, so that we can modify the trees */
	lock_basic_lock(&env->anchors->lock);
	tp2 = (struct trust_anchor*)rbtree_search(env->anchors->tree, &key);
	if(!tp2) {
		verbose(VERB_ALGO, "trustpoint was deleted in set_next_probe");
		lock_basic_unlock(&env->anchors->lock);
		return 0;
	}
	log_assert(tp == tp2);
	lock_basic_lock(&tp->lock);

	/* schedule */
	mold = wait_probe_time(env->anchors);
	(void)rbtree_delete(&env->anchors->autr->probe, tp);
	tp->autr->next_probe_time = calc_next_probe(env, 
		tp->autr->query_interval);
	(void)rbtree_insert(&env->anchors->autr->probe, &tp->autr->pnode);
	mnew = wait_probe_time(env->anchors);

	lock_basic_unlock(&env->anchors->lock);
	verbose(VERB_ALGO, "next probe set in %d seconds", 
		(int)tp->autr->next_probe_time - (int)*env->now);
	if(mold != mnew) {
		reset_worker_timer(env);
	}
	return 1;
}