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
struct fs_base {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; int /*<<< orphan*/  list; int /*<<< orphan*/  users_refcount; struct fs_base* parent; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,void (*) (struct kref*)) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _fs_put(struct fs_base *node, void (*kref_cb)(struct kref *kref),
		    bool parent_locked)
{
	struct fs_base *parent_node = node->parent;

	if (parent_node && !parent_locked)
		mutex_lock(&parent_node->lock);
	if (atomic_dec_and_test(&node->users_refcount)) {
		if (parent_node) {
			/*remove from parent's list*/
			list_del_init(&node->list);
			mutex_unlock(&parent_node->lock);
		}
		kref_put(&node->refcount, kref_cb);
		if (parent_node && parent_locked)
			mutex_lock(&parent_node->lock);
	} else if (parent_node && !parent_locked) {
		mutex_unlock(&parent_node->lock);
	}
}