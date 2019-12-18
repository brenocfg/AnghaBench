#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct master {TYPE_2__* match; } ;
struct device {int dummy; } ;
struct component {int dummy; } ;
struct TYPE_4__ {size_t num; TYPE_1__* compare; } ;
struct TYPE_3__ {struct component* component; int /*<<< orphan*/  duplicate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct master* __master_find (struct device*,int /*<<< orphan*/ *) ; 
 int component_bind (struct component*,struct master*,void*) ; 
 int /*<<< orphan*/  component_mutex ; 
 int /*<<< orphan*/  component_unbind (struct component*,struct master*,void*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

int component_bind_all(struct device *master_dev, void *data)
{
	struct master *master;
	struct component *c;
	size_t i;
	int ret = 0;

	WARN_ON(!mutex_is_locked(&component_mutex));

	master = __master_find(master_dev, NULL);
	if (!master)
		return -EINVAL;

	/* Bind components in match order */
	for (i = 0; i < master->match->num; i++)
		if (!master->match->compare[i].duplicate) {
			c = master->match->compare[i].component;
			ret = component_bind(c, master, data);
			if (ret)
				break;
		}

	if (ret != 0) {
		for (; i > 0; i--)
			if (!master->match->compare[i - 1].duplicate) {
				c = master->match->compare[i - 1].component;
				component_unbind(c, master, data);
			}
	}

	return ret;
}