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
struct list_head {int dummy; } ;
struct gov_attr_set {unsigned int usage_count; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (struct list_head*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

unsigned int gov_attr_set_put(struct gov_attr_set *attr_set, struct list_head *list_node)
{
	unsigned int count;

	mutex_lock(&attr_set->update_lock);
	list_del(list_node);
	count = --attr_set->usage_count;
	mutex_unlock(&attr_set->update_lock);
	if (count)
		return count;

	kobject_put(&attr_set->kobj);
	mutex_destroy(&attr_set->update_lock);
	return 0;
}