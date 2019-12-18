#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct trust_anchor {TYPE_2__* autr; int /*<<< orphan*/  lock; } ;
struct module_env {scalar_t__* now; TYPE_3__* anchors; } ;
struct TYPE_10__ {scalar_t__ key; } ;
typedef  TYPE_4__ rbnode_type ;
struct TYPE_9__ {int /*<<< orphan*/  lock; TYPE_1__* autr; } ;
struct TYPE_8__ {int /*<<< orphan*/  pnode; int /*<<< orphan*/  retry_time; scalar_t__ next_probe_time; } ;
struct TYPE_7__ {int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 TYPE_4__* RBTREE_NULL ; 
 scalar_t__ calc_next_probe (struct module_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,struct trust_anchor*) ; 
 TYPE_4__* rbtree_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct trust_anchor*
todo_probe(struct module_env* env, time_t* next)
{
	struct trust_anchor* tp;
	rbnode_type* el;
	/* get first one */
	lock_basic_lock(&env->anchors->lock);
	if( (el=rbtree_first(&env->anchors->autr->probe)) == RBTREE_NULL) {
		/* in case of revoked anchors */
		lock_basic_unlock(&env->anchors->lock);
		/* signal that there are no anchors to probe */
		*next = 0;
		return NULL;
	}
	tp = (struct trust_anchor*)el->key;
	lock_basic_lock(&tp->lock);

	/* is it eligible? */
	if((time_t)tp->autr->next_probe_time > *env->now) {
		/* no more to probe */
		*next = (time_t)tp->autr->next_probe_time - *env->now;
		lock_basic_unlock(&tp->lock);
		lock_basic_unlock(&env->anchors->lock);
		return NULL;
	}

	/* reset its next probe time */
	(void)rbtree_delete(&env->anchors->autr->probe, tp);
	tp->autr->next_probe_time = calc_next_probe(env, tp->autr->retry_time);
	(void)rbtree_insert(&env->anchors->autr->probe, &tp->autr->pnode);
	lock_basic_unlock(&env->anchors->lock);

	return tp;
}