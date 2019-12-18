#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct views {int /*<<< orphan*/  lock; int /*<<< orphan*/  vtree; } ;
struct TYPE_2__ {struct view** key; } ;
struct view {char* name; int /*<<< orphan*/  lock; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,TYPE_1__*) ; 

struct view*
views_find_view(struct views* vs, const char* name, int write)
{
	struct view* v;
	struct view key;
	key.node.key = &v;
	key.name = (char *)name;
	lock_rw_rdlock(&vs->lock);
	if(!(v = (struct view*)rbtree_search(&vs->vtree, &key.node))) {
		lock_rw_unlock(&vs->lock);
		return 0;
	}
	if(write) {
		lock_rw_wrlock(&v->lock);
	} else {
		lock_rw_rdlock(&v->lock);
	}
	lock_rw_unlock(&vs->lock);
	return v;
}