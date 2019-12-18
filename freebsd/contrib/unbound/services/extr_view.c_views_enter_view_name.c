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
struct views {int /*<<< orphan*/  lock; int /*<<< orphan*/  vtree; } ;
struct view {int /*<<< orphan*/  lock; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_warn (char*,char*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct view* view_create (char*) ; 
 int /*<<< orphan*/  view_delete (struct view*) ; 

__attribute__((used)) static struct view*
views_enter_view_name(struct views* vs, char* name)
{
	struct view* v = view_create(name);
	if(!v) {
		log_err("out of memory");
		return NULL;
	}

	/* add to rbtree */
	lock_rw_wrlock(&vs->lock);
	lock_rw_wrlock(&v->lock);
	if(!rbtree_insert(&vs->vtree, &v->node)) {
		log_warn("duplicate view: %s", name);
		lock_rw_unlock(&v->lock);
		view_delete(v);
		lock_rw_unlock(&vs->lock);
		return NULL;
	}
	lock_rw_unlock(&vs->lock);
	return v;
}