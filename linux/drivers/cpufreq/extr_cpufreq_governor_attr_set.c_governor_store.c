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
struct kobject {int dummy; } ;
struct governor_attr {int (* store ) (struct gov_attr_set*,char const*,size_t) ;} ;
struct gov_attr_set {int /*<<< orphan*/  update_lock; scalar_t__ usage_count; } ;
struct attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct gov_attr_set*,char const*,size_t) ; 
 struct governor_attr* to_gov_attr (struct attribute*) ; 
 struct gov_attr_set* to_gov_attr_set (struct kobject*) ; 

__attribute__((used)) static ssize_t governor_store(struct kobject *kobj, struct attribute *attr,
			      const char *buf, size_t count)
{
	struct gov_attr_set *attr_set = to_gov_attr_set(kobj);
	struct governor_attr *gattr = to_gov_attr(attr);
	int ret;

	mutex_lock(&attr_set->update_lock);
	ret = attr_set->usage_count ? gattr->store(attr_set, buf, count) : -EBUSY;
	mutex_unlock(&attr_set->update_lock);
	return ret;
}